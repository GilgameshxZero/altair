/*
ID: yangchess1
LANG: C++
PROB: cryptcow
*/

#include <iostream>
#include <memory.h>
#include <fstream>
#include <string>

using namespace std;

const int MAX = 100;
const int MOD = 131071;
const int LEN = 47;
const string plaintext = "Begin the Escape execution at the Break of Dawn";

ifstream fin("cryptcow.in");
ofstream fout("cryptcow.out");

bool visited[MOD+1];

inline bool ELFHash(string s, int length){
    unsigned long h=0,g;
    for (int i=0; i<length; i++){
        h=(h<<4)+s[i];
        g=h&0xf0000000l;
        if(g){
            h^=g>>24;
        }
        h&=~g;
    }

    h = h%MOD;

    if(visited[h])
        return true;
    else{
        visited[h] = true;
        return false;
    }
}

void dfs(string s, int num){

    if(plaintext == s){
        fout<<1<<" "<<num<<endl;
        exit(0);
    }

    int length = s.length();

    if(ELFHash(s, length)) return ;

    
    int cnt=0, c_cnt=0, o_cnt=0, w_cnt=0;
    int c[MAX], o[MAX], w[MAX], label[MAX];
    memset(c, 0, sizeof(c));
    memset(o, 0, sizeof(o));
    memset(w, 0, sizeof(w));
    memset(label, 0, sizeof(label));

    int i,j,k;
    label[cnt++] = -1;
    for(i = 0; i<length; ++i){
        if(s[i] == 'C'){

            c[c_cnt++] = i;
            label[cnt++] = i;

        }else if(s[i] == 'O'){

            o[o_cnt++] = i;
            label[cnt++] = i;

        }else if(s[i] == 'W'){

            w[w_cnt++] = i;
            label[cnt++] = i;
        }
    }
    label[cnt++] = length;

    if(c_cnt!=o_cnt || o_cnt!=w_cnt)
        return;


    for(i=0; i<cnt-1; ++i){
        if(label[i]+1 < label[i+1]){
            string sub = s.substr(label[i]+1, label[i+1]-label[i]-1);
            if(plaintext.find(sub)==string::npos)
                return;
        }
    }

    for(i=0; i<o_cnt; ++i){
        for(j=0; j<c_cnt; ++j){
            for(k=w_cnt-1; k>=0; --k){
                if(c[j]<o[i] && o[i]<w[k]){
                    string t1 = s.substr(0, c[j]);
                    string t2 = s.substr(o[i]+1, w[k]-o[i]-1);
                    string t3 = s.substr(c[j]+1, o[i]-c[j]-1);
                    string t4 = s.substr(w[k]+1, length-w[k]);
                    string t = t1+t2+t3+t4;
                    dfs(t, num+1);
                }
            }
        }
    }
}

int main(){

    string s;

    getline(fin, s);

    int length = s.length();

    if( (length-LEN)%3 !=0 ){
        fout<<"0 0"<<endl;
        return 0;
    }

    dfs(s,0);

    fout<<"0 0"<<endl;

    return 0;
}

/*
Some optimizations are needed for this problem. They are listed below:

1. Check the length of the encrypted message to be the length of the desired message plus a number of length 3's (the COW).
2. A legitimate encrypted message must have the same number of letters for each letter as the desired message, disregarding the 'COW's.
3. There must be as many C's as O's as W's in the message.
4. The part before the first C and after the last W must be a prefix and suffix of the desired message.
5. The part of the message between every C, O, or W must be in the desired message.
6. The first encoding letter must be a C, and the last a W.
7. Hash the strings in the main DFS to avoid doing the same strings twice.

You may also see that we often use the number 9. It can be calculated that this is the greatest amount of encryptions possible to a message because of the length limit of the input.
*/
/*
#include <fstream>
#include <string>

//A node of the hash table for collison resolving.
struct HTNode
{
	std::string message;
	HTNode *next_node;
};

const int HASH_TABLE_SIZE = 10000;

HTNode hash_table[HASH_TABLE_SIZE];

int HashString (std::string string)
{
	int a, length = string.length (), rtrn = 0;

	for (a = 0;a < length;a++)
		rtrn = rtrn * 256 + string[a];

	return rtrn % HASH_TABLE_SIZE;
}

bool InHashTable (std::string string)
{
	HTNode *local_copy = &hash_table[HashString (string)];
	
	while (local_copy != NULL)
	{
		if (local_copy->message == string)
			return true;

		local_copy = local_copy->next_node;
	}

	return false;
}

int main ()
{
	const int MAX_ENCRYPTIONS = 9;

	std::ifstream in ("cryptcow.in");
	std::ofstream out ("cryptcow.out");
	std::string temp_str, encrypt_message, desire_message = "Begin the Escape execution at the Break of Dawn";
	HTNode *temp_node;
	bool found;
	char buffer;
	int depth, message_length, desire_length, firstC, lastW, letter_pos[MAX_ENCRYPTIONS][3], letter_count[2][256];
	int a, b, c;

	//Input
	{
		//Read until we encounter a newline.
		while (true)
		{
			buffer = in.get ();

			if (buffer == '\n')
				break;

			encrypt_message += buffer;
		}

		in.close ();
	}

	//Initialize.
	{
		for (a = 0;a < HASH_TABLE_SIZE;a++)
		{
			hash_table[a].message = "";
			hash_table[a].next_node = NULL;
		}

		message_length = static_cast<int>(encrypt_message.length ());
		desire_length = static_cast<int>(desire_message.length ());
	}

	//Optimization 1: check the length of the encrypted message to be valid, ie it is the original message plus a number of 'COW's.
	{
		if (message_length < desire_length || (message_length - desire_length) % 3 != 0)
		{
			out << "0 0\n";
			out.close ();

			return 0;
		}
	}

	//Optimization 2: first count up the letters in each of the messages.
	{
		for (a = 0;a < 2;a++)
			for (b = 0;b < 128;b++)
				letter_count[a][b] = 0;

		for (a = 0;a < message_length;a++)
			letter_count[0][encrypt_message[a]]++;

		for (a = 0;a < desire_length;a++)
			letter_count[1][desire_message[a]]++;

		//See if there is the same amount of non-COW letters in each of the messages.
		for (a = 0;a < 128;a++)
		{
			if (a == 'C' || a == 'O' || a == 'W')
				continue;

			if (letter_count[0][a] != letter_count[1][a])
			{
				out << "0 0\n";
				out.close ();

				return 0;
			}
		}
	}

	//Optimization 3: check that the # of C's, O's, and W's is the same.
	{
		if (!(letter_count[0]['C'] == letter_count[0]['O'] && letter_count[0]['C'] == letter_count[0]['W']))
		{
			out << "0 0\n";
			out.close ();

			return 0;
		}
	}

	//Start an in-place DFS of the letter combinations.
	{
		depth = 0;

		for (a = 0;a < MAX_ENCRYPTIONS;a++)
			for (b = 0;b < 3;b++)
				letter_pos[a][b] = -1;
	}

	while (depth != -1)
	{
		//Check if we are at the depth limit.
		if (depth == letter_count[0]['C'])
		{
			//We have decrypted it wholly. Check if the decrypted message is the desired one.
			if (encrypt_message == desire_message)
			{
				out << "1 " << depth << "\n";
				out.close ();

				return 0;
			}
			else
				depth--;
		}
		else
		{
			//If we have already been to this depth and decrypted the message, we need to encrypt it again using the saved letter data.
			{
			if (letter_pos[depth][0] != -1)
				encrypt_message = encrypt_message.substr (0, letter_pos[depth][0]) + "C" + encrypt_message.substr (letter_pos[depth][0] + letter_pos[depth][2] - letter_pos[depth][1] - 1, letter_pos[depth][1] - letter_pos[depth][0] - 1) + "O" + encrypt_message.substr (letter_pos[depth][0], letter_pos[depth][2] - letter_pos[depth][1] - 1) + "W" + encrypt_message.substr (letter_pos[depth][2] - 2, encrypt_message.length () - letter_pos[depth][2] + 2);
			}
			
			message_length = static_cast<int>(encrypt_message.length ());

			//Optimization 4 and 6: take the part before the first C and see if that is the beginning of the desired message, and do the same with the part after the last W. Also check the first and last encoding letters.
			{
				temp_str = "";

				for (a = 0;a < message_length && encrypt_message[a] != 'C';a++)
				{
					if (encrypt_message[a] == 'O' || encrypt_message[a] == 'W')
						break;

					temp_str += encrypt_message[a];
				}

				//Optimization 6.
				if (encrypt_message[a] == 'O' || encrypt_message[a] == 'W')
				{
					letter_pos[depth][0] = letter_pos[depth][1] = letter_pos[depth][2] = -1;
					depth--;
					continue;
				}
			
				firstC = a;

				if (desire_message.substr (0, temp_str.length ()) != temp_str)
				{
					letter_pos[depth][0] = letter_pos[depth][1] = letter_pos[depth][2] = -1;
					depth--;
					continue;
				}

				temp_str = "";

				for (a = message_length - 1;a >= 0 && encrypt_message[a] != 'W';a--)
				{
					if (encrypt_message[a] == 'C' || encrypt_message[a] == 'O')
						break;

					temp_str = encrypt_message[a] + temp_str;
				}

				//Optimization 6.
				if (encrypt_message[a] == 'C' || encrypt_message[a] == 'O')
				{
					letter_pos[depth][0] = letter_pos[depth][1] = letter_pos[depth][2] = -1;
					depth--;
					continue;
				}

				lastW = a;

				if (desire_message.substr (desire_message.length () - temp_str.length (), temp_str.length ()) != temp_str)
				{
					letter_pos[depth][0] = letter_pos[depth][1] = letter_pos[depth][2] = -1;
					depth--;
					continue;
				}
			}

			//Optimization 5.
			{
				temp_str = "";
				
				for (a = firstC + 1;a <= lastW;a++)
				{
					if (encrypt_message[a] != 'C' && encrypt_message[a] != 'O' && encrypt_message[a] != 'W')
						temp_str += encrypt_message[a];
					else
					{
						b = temp_str.length ();

						if (b != 0)
						{
							found = false;

							//Search for a substring temp_str in the desired message. If it isn't found, go back one depth.
							for (c = 0;c < desire_length - b;c++)
							{
								if (desire_message.substr (c, b) == temp_str)
								{
									found = true;
									break;
								}
							}

							temp_str = "";

							if (found == false)
								break;
						}
					}
				}

				if (found == false)
				{
					letter_pos[depth][0] = letter_pos[depth][1] = letter_pos[depth][2] = -1;
					depth--;
					continue;
				}
			}

			//Pick a C, O, and W from the message and decrypt it once, while recording the positions of the letters. Make sure to start at the beginning if it is the first time visiting this depth, if not, then start at the letter after whatever letter was chosen last time at this depth (that's kind of why we recorded it, and also because we want to be able to reverse a decrypted string). Put in a check to see that the positions we picked are valid too (C < O < W).
			{
				found = false;

				for (a = letter_pos[depth][0] + 1;a < message_length;a++)
				{
					//Look for an O.
					if ((letter_pos[depth][0] != -1))
					{
						for (b = letter_pos[depth][1] + 1;b < message_length;b++)
						{
							//Look for a W.
							if ((letter_pos[depth][0] < letter_pos[depth][1]) && (letter_pos[depth][1] != -1))
							{
								for (c = letter_pos[depth][2] + 1;c < message_length;c++)
								{
									if ((encrypt_message[c] == 'W') && (c > letter_pos[depth][1])) //We will use this W, so record its position.
									{
										letter_pos[depth][2] = c;
										found = true;
										break;
									}
								}
							}

							if (found == true)
								break;

							if (encrypt_message[b] == 'O') //We will use this O, so record its position, and rechoose a W.
							{
								letter_pos[depth][1] = b;
								letter_pos[depth][2] = -1;
							}
						}
					}
				
					if (found == true)
						break;

					if (encrypt_message[a] == 'C') //We will use this C, so record its position, and rechoose an O.
					{
						letter_pos[depth][0] = a;
						letter_pos[depth][1] = -1;
					}
				}
			}

			//Execute the decryption if we found a triplet, if not, go back 1 depth.
			{
				if (found == true)
				{
					//Now encrypt the message and increment depth. Take out the COW we looked for and swap the message between CO and OW.
					encrypt_message = encrypt_message.substr (0, letter_pos[depth][0]) + encrypt_message.substr (letter_pos[depth][1] + 1, letter_pos[depth][2] - letter_pos[depth][1] - 1) + encrypt_message.substr (letter_pos[depth][0] + 1, letter_pos[depth][1] - letter_pos[depth][0] - 1) + encrypt_message.substr (letter_pos[depth][2] + 1, encrypt_message.length () - letter_pos[depth][2] - 1);
	
					//Optimization 7: Have we tested this string before?
					{
						if (InHashTable (encrypt_message))
							continue;
						else
						{
							a = HashString (encrypt_message);
							temp_node = &hash_table[a];
			
							while (temp_node->next_node != NULL)
								temp_node = temp_node->next_node;

							temp_node->message = encrypt_message;
							temp_node->next_node = new HTNode;
							temp_node->next_node->message = "";
							temp_node->next_node->next_node = NULL;
							depth++;
						}
					}
				}
				else
				{
					letter_pos[depth][0] = letter_pos[depth][1] = letter_pos[depth][2] = -1;
					depth--;
				}
			}
		}
	}

	//No solutions were found.
	out << "0 0\n";
	out.close ();

	return 0;
}*/