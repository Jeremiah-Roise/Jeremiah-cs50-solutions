#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define UNUSED(x) (void)(x)

// preferences[i][j] is number of voters who prefer i over j
// voters
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];


// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];



int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");



    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (size_t i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            //  success we have a real candidate
            ranks[rank] = i;
            return true;
        }
    }
    
    
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //  take ranks and put into preference array
    //  like | alice |  bob  |charlie|
    //       =========================
    //  alice|   0   |   3   |   5   |
    //    bob|   1   |   0   |   1   |
    //charlie|   1   |   1   |   0   |

    for (size_t i = 0; i < candidate_count; i++)
    {
        for (size_t j = 0; j < candidate_count; j++)
        {
            if (ranks[i] != ranks[j] && i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
            //    to set up the diagonal split.
            else
            {
                preferences[i][i] = 0;
            }
        }
    }

    return;
}

// is a simple way to add a pair to the pairs graph.
static void pairAssign(const size_t winner, const size_t loser)
{
    pairs[pair_count].winner = winner;
    pairs[pair_count].loser = loser;
    pair_count++;
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (size_t i = 0; i < candidate_count; i++)
    {
        for (size_t j = i + 1; j < candidate_count; j++)
        { 
            //    prevents candidates being paired with themselves
            if (j != i)
            {
                size_t a = preferences[i][j];
                size_t b = preferences[j][i];
                if (a > b)
                {
                    pairAssign(i, j);
                }
                if (a < b)
                {
                    pairAssign(j, i);
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    size_t range = 0;
    size_t nextlargest;
    for (size_t i = 0; i < pair_count; i++)
    {

        size_t largest = 0;
        for (size_t j = range; j < pair_count; j++)
        {
            size_t score = preferences[pairs[j].winner][pairs[j].loser];

            if (score > largest)
            {
                largest = score;
                nextlargest = j;
            }
        }
        if (largest != 0)
        {
            pair tmp = pairs[range];
            pairs[range] = pairs[nextlargest];
            pairs[nextlargest] = tmp;
            range++;
        }
    }
    return;
}

// declares functions for recursive functions.
bool is_cycle(size_t winner, size_t loser);
// defines the recursive function.
bool is_cycle(size_t winner, size_t loser)
{
    if (winner == loser)
    {
        return true;
    }
    for (size_t i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (is_cycle(winner, i)) 
            {
                return true;
            }
        }
    }
    return false;
}

// locks a pair in the locked graph.
void lockPair(const pair *Target)
{
    locked[Target->winner][Target->loser] = true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // loop and find non circular chain of pairs
    for (size_t i = 0; i < pair_count; i++) 
    {
        if (is_cycle(pairs[i].winner, pairs[i].loser) == false)
        {
            // lock pairs in graph
            lockPair(&pairs[i]);
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    size_t winner = -1;
    for (size_t i = 0; i < candidate_count; i++)
    {
        size_t sum = 0;
        for (size_t j = 0; j < candidate_count; j++)
        {
            sum += locked[j][i];
        }
        if (sum == 0)
        {
            winner = i;
        }
    }
    printf("%s\n", candidates[winner]);
    return;
}
