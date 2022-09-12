/*
ID: yangchess1
LANG: C++
PROG: shopping
*/

//ALGORITHM: A pretty obvious DP problem, with a few dimensions, see lesson on DP. It's kind of like the knapsack problem, but with several dimensions

#include <fstream>

const int MAX_ITEMCODE = 999;
const int MAX_ITEMDIV = 5;
const int MAX_OFFERCITEM = 5;
const int MAX_COFFER = 99;
const int INFINITY = 100000000;

//Stores and item and it's amount in the offer
struct ItemNum
{
	int code;
	int number;
};

//Stores an offer
struct Offer
{
	int cItem;
	int price;
	ItemNum Item[MAX_OFFERCITEM];
};

//The POWERHOUSE of this program, a recursive function that calculates the low_price for any set of products given common variables. item_code: converts a hash basket item to its code. code_item: converts an item code to its hash basket value (large array).
void Calc_Low (int cOffer, int *target, int *item_ref, int *Iprice, int (*low_price)[6][6][6][6], Offer *Offers)
{
	//Is low_price already calculated?
	if (low_price[target[0]][target[1]][target[2]][target[3]][target[4]] != -1)
		return;

	//Need to calculate (that's the purpose of this function! To ensure that low_price for the target is calculated)
	int small_price = INFINITY, temp[5];
	int a, b;
	bool pass;

	//Test if we can substitue an offer into the target to acheive a better price:
	for (a = 0;a < cOffer;a++) //Loop the offers
	{
		//Reset the temp array (we are going to pass this to Calc_Low) equal to target
		for (b = 0;b < MAX_ITEMDIV;b++)
			temp[b] = target[b];
		
		//Reset the flag
		pass = true;

		//The offers' item codes come in reference to the basket. So, all we need to do is check for error code as we check whether we can fit the offer in the target.
		for (b = 0;b < Offers[a].cItem;b++)
		{
			if (Offers[a].Item[b].code == -1) //If the product offered in the offer is not even what we want
			{
				pass = false;
				break;
			}
			else if (Offers[a].Item[b].number > temp[Offers[a].Item[b].code]) //If we can't even fit the offer in the target
			{
				pass = false;
				break;
			}
			else //If the offer can be substituted, subtract that from temp
				temp[Offers[a].Item[b].code] -= Offers[a].Item[b].number;
		}

		if (pass == true) //If we can substitute part of our target for the offer[a], and we have with temp
		{
			//Generate the low_price for temp
			Calc_Low (cOffer, temp, item_ref, Iprice, low_price, Offers);

			//Test if the price of the offer plus the price of temp is less than the small_price
			if (Offers[a].price + low_price[temp[0]][temp[1]][temp[2]][temp[3]][temp[4]] < small_price)
				small_price = Offers[a].price + low_price[temp[0]][temp[1]][temp[2]][temp[3]][temp[4]];
		}
	}

	//Can we subtract products from the target to get a better price than small_price?
	for (a = 0;a < MAX_ITEMDIV;a++)
	{
		//Reset the temp array (we are going to pass this to Calc_Low) equal to target
		for (b = 0;b < MAX_ITEMDIV;b++)
			temp[b] = target[b];

		//Make sure that we have at least 1 item in the target
		if (temp[a] > 0)
		{
			temp[a]--;

			//Generate the low_price for temp
			Calc_Low (cOffer, temp, item_ref, Iprice, low_price, Offers);

			//Test if the price of the product plus the price of temp is less than the small_price
			if (Iprice[item_ref[a] - 1] + low_price[temp[0]][temp[1]][temp[2]][temp[3]][temp[4]] < small_price)
				small_price = Iprice[item_ref[a] - 1] + low_price[temp[0]][temp[1]][temp[2]][temp[3]][temp[4]];
		}
	}

	//The lowest price is small_price
	low_price[target[0]][target[1]][target[2]][target[3]][target[4]] = small_price;

	return;
}

int main ()
{
	std::ifstream in;
	std::ofstream out;
	Offer Offers[MAX_COFFER]; //An array of Offer[cOffers]
	int cOffer, Iprice[MAX_ITEMCODE], target[MAX_OFFERCITEM], item_ref[MAX_OFFERCITEM], basket_ref[MAX_ITEMCODE], low_price[MAX_ITEMDIV + 1][MAX_ITEMDIV + 1][MAX_ITEMDIV + 1][MAX_ITEMDIV + 1][MAX_ITEMDIV + 1];
	int a, b, c, d, e; //Temporary variables

	//INPUT/INITIALIZATION
	for (a = 0;a < MAX_ITEMCODE;a++)
		basket_ref[a] = -1;

	in.open ("shopping.in");
	in >> cOffer;

	//Loop input
	for (a = 0;a < cOffer;a++)
	{
		//Read in number of items in offer and initialize pOffer[a].pItem
		in >> Offers[a].cItem;

		//Read in items and their number
		for (c = 0;c < Offers[a].cItem;c++)
			in >> Offers[a].Item[c].code >> Offers[a].Item[c].number;

		//Read price
		in >> Offers[a].price;
	}

	//Second part of input
	in >> a;

	//Since a is the number of items we want, we will take the first 5 - a elements as 0
	for (b = 0;b < MAX_ITEMDIV - a;b++)
		item_ref[b] = target[b] = 0;

	for (b = MAX_ITEMDIV - a;b < MAX_ITEMDIV;b++)
	{
		in >> item_ref[b];
		in >> target[b] >> Iprice[item_ref[b] - 1];
		basket_ref[item_ref[b] - 1] = b;
	}

	in.close ();

	for (a = 0;a < 6;a++)
		for (b = 0;b < 6;b++)
			for (c = 0;c < 6;c++)
				for (d = 0;d < 6;d++)
					for (e = 0;e < 6;e++)
						low_price[a][b][c][d][e] = -1; //Error code

	//The price for 0 items is always 0. Set all others equal to -1 so that our recursive function knows which are already calculated, and is easier to program (this was done in the loop before).
	low_price[0][0][0][0][0] = 0;

	//INPUT/INITIALIZATION END. ALGORITHM START
	//We want to mark the offers we cannot use because we cannot use one of their products and  relate the products to the number of the product we want to buy (ie 1 - 5). We use basket_ref for this purpose.
	for (a = 0;a < cOffer;a++)
		for (b = 0;b < Offers[a].cItem;b++)
			Offers[a].Item[b].code = basket_ref[Offers[a].Item[b].code - 1];

	//We need a recursive function to calculate all possible cases considering that we do not know the number of items we need to buy (item_div (item diversity)) beforehand.
	Calc_Low (cOffer, target, item_ref, Iprice, low_price, Offers);

	//ALGORITHM END. OUTPUT/END START
	out.open ("shopping.out");
	out << low_price[target[0]][target[1]][target[2]][target[3]][target[4]] << "\n";
	out.close ();

	return 0;
}