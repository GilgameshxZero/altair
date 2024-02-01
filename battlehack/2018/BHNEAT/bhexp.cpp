#include "bhexp.h"

//Perform evolution on XOR, for gens generations
Population *bh_test (int gens) {
	Population *pop = 0;
	Genome *start_genome;
	char curword[20];
	int id;

	ostringstream *fnamebuf;
	int gen;

	std::vector<int> evals (NEAT::num_runs, 0), genes (NEAT::num_runs, 0), nodes (NEAT::num_runs, 0); //hold record for each run
	int winnernum;
	int winnergenes;
	int winnernodes;
	//For averaging
	int totalevals = 0;
	int totalgenes = 0;
	int totalnodes = 0;
	int expcount;
	int samples;  //For averaging

	ifstream iFile ("bhstartgenes", ios::in);

	cout << "START BH TEST" << endl;

	cout << "Reading in the start genome" << endl;
	//Read in the start Genome
	iFile >> curword;
	iFile >> id;
	cout << "Reading in Genome id " << id << endl;
	start_genome = new Genome (id, iFile);
	iFile.close ();

	for (expcount = 0; expcount < NEAT::num_runs; expcount++) {
		//Spawn the Population
		cout << "Spawning Population off Genome2" << endl;

		pop = new Population (start_genome, NEAT::pop_size);

		cout << "Verifying Spawned Pop" << endl;
		pop->verify ();

		for (gen = 1; gen <= gens; gen++) {
			cout << "Epoch " << gen << endl;

			//This is how to make a custom filename
			fnamebuf = new ostringstream ();
			(*fnamebuf) << "output\\gen_" << gen << ends;  //needs end marker

#ifndef NO_SCREEN_OUT
			cout << "name of fname: " << fnamebuf->str () << endl;
#endif

			char temp[50];
			sprintf (temp, "output\\gen_%d", gen);

			//Check for success
			if (bh_epoch (pop, gen, temp, winnernum, winnergenes, winnernodes)) {
				//	if (xor_epoch(pop,gen,fnamebuf->str(),winnernum,winnergenes,winnernodes)) {
				//Collect Stats on end of experiment
				evals[expcount] = NEAT::pop_size*(gen - 1) + winnernum;
				genes[expcount] = winnergenes;
				nodes[expcount] = winnernodes;
				gen = gens;

			}

			//Clear output filename
			fnamebuf->clear ();
			delete fnamebuf;

		}

		if (expcount < NEAT::num_runs - 1) delete pop;

	}

	//Average and print stats
	cout << "Nodes: " << endl;
	for (expcount = 0; expcount < NEAT::num_runs; expcount++) {
		cout << nodes[expcount] << endl;
		totalnodes += nodes[expcount];
	}

	cout << "Genes: " << endl;
	for (expcount = 0; expcount < NEAT::num_runs; expcount++) {
		cout << genes[expcount] << endl;
		totalgenes += genes[expcount];
	}

	cout << "Evals " << endl;
	samples = 0;
	for (expcount = 0; expcount < NEAT::num_runs; expcount++) {
		cout << evals[expcount] << endl;
		if (evals[expcount] > 0)
		{
			totalevals += evals[expcount];
			samples++;
		}
	}

	cout << "Failures: " << (NEAT::num_runs - samples) << " out of " << NEAT::num_runs << " runs" << endl;
	cout << "Average Nodes: " << (samples > 0 ? (double)totalnodes / samples : 0) << endl;
	cout << "Average Genes: " << (samples > 0 ? (double)totalgenes / samples : 0) << endl;
	cout << "Average Evals: " << (samples > 0 ? (double)totalevals / samples : 0) << endl;

	return pop;
}

int bh_epoch (Population *pop, int generation, char *filename, int &winnernum, int &winnergenes, int &winnernodes) {
	vector<Organism*>::iterator curorg;
	vector<Species*>::iterator curspecies;
	//char cfilename[100];
	//strncpy( cfilename, filename.c_str(), 100 );

	//ofstream cfilename(filename.c_str());

	bool win = false;

	//Evaluate each organism on a test
	//NEW
	{
		//generate python file corresponding to all organisms
		ifstream bhtemin ("bh-template.py");
		stringstream ss;
		ss << bhtemin.rdbuf ();
		bhtemin.close ();
		string bhtem = ss.str ();

		ofstream pyout;
		vector<int> contestants;

		for (int a = 0; a < pop->organisms.size (); a++) {
			contestants.push_back (a);

			Organism &thisorg = *(pop->organisms[a]);
			Network &thisnet = *thisorg.net;

			//build map from nodes
			map<NNode *, int> nmap;
			for (int b = 0; b < thisnet.genotype->nodes.size (); b++)
				nmap.insert (make_pair (thisnet.genotype->nodes[b], b));

			//go through genes, output properties of enabled ones before template
			string orgid = IntToString (generation) + "_" + IntToString (a);
			string filename = "organisms\\Generation_" + orgid + ".py";
			pyout.open (filename);
			pyout << setprecision (15) << "" << "edge = [";
			for (int b = 0; b < thisnet.genotype->genes.size (); b++) {
				Gene &thisgene = *thisnet.genotype->genes[b];
				if (thisgene.enable) {
					pyout << "(" << nmap[thisgene.lnk->in_node] << "," << 
						nmap[thisgene.lnk->out_node] << "," << thisgene.lnk->weight << ")";
					if (b != thisnet.genotype->genes.size () - 1)
						pyout << ",";
				}
			}
			pyout << "]\norgname=\'BHNEAT_" << orgid << "\'\n"
				<< "cnodes = " << thisnet.genotype->nodes.size () << "\n\n" << bhtem;
			pyout.close ();
		}

		//run single elimination tournament on all organisms
		//system ("start battlehack start");
		//std::this_thread::sleep_for (std::chrono::milliseconds (2000));
		//string s = exec ("start battlehack start");
		std::vector<int> cranking (contestants.size (), 0);
		vector<thread> th;
		string k;
		for (int rank = 1;contestants.size () != 1;rank++) {
			for (int a = 0; a < contestants.size (); a++) {
				string orgid = IntToString (generation) + "_" + IntToString (contestants[a]);
				string filename = "organisms\\Generation_" + orgid + ".py";
				th.push_back (thread (RunBot, filename));
				std::this_thread::sleep_for (std::chrono::milliseconds (500));

				if (th.size () == 8) {
					for (int a = th.size () - 1; a >= 0; a--) {
						th[a].join ();
						th.pop_back ();
					}
				}
			}
			
			//wait for all games to finish
			for (int a = th.size () - 1; a >= 0; a--) {
				th[a].join ();
				th.pop_back ();
			}

			//determine winners
			vector<int> winners;
			for (int a = 0; a < contestants.size (); a += 2) {
				string orgid = IntToString (generation) + "_" + IntToString (contestants[a]);
				ifstream in ("result\\BHNEAT_" + orgid + ".txt");
				int count[2];
				in >> count[0];
				in.close ();
				orgid = IntToString (generation) + "_" + IntToString (contestants[a + 1]);
				in.open ("result\\BHNEAT_" + orgid + ".txt");
				in >> count[1];
				in.close ();

				if (count[0] > count[1])
					winners.push_back (contestants[a]);
				else
					winners.push_back (contestants[a + 1]);
			}
			contestants = winners;
			for (int a = 0; a < contestants.size (); a++)
				cranking[contestants[a]] = rank;
		}

		cout << "WINNER GEN " << generation << ": " << contestants[0] << "\n";

		//assign fitness based on tournament results
		for (int a = 0; a < pop->organisms.size (); a++) {
			Organism &thisorg = *(pop->organisms[a]);
			thisorg.fitness = cranking[a] * 10 + generation;
		}
	}

	//Average and max their fitnesses for dumping to file and snapshot
	for (curspecies = (pop->species).begin (); curspecies != (pop->species).end (); ++curspecies) {

		//This experiment control routine issues commands to collect ave
		//and max fitness, as opposed to having the snapshot do it, 
		//because this allows flexibility in terms of what time
		//to observe fitnesses at

		(*curspecies)->compute_average_fitness ();
		(*curspecies)->compute_max_fitness ();
	}

	//Take a snapshot of the population, so that it can be
	//visualized later on
	//if ((generation%1)==0)
	//  pop->snapshot();

	//Only print to file every print_every generations
	if (win ||
		((generation % (NEAT::print_every)) == 0))
		pop->print_to_file_by_species (filename);


	if (win) {
		for (curorg = (pop->organisms).begin (); curorg != (pop->organisms).end (); ++curorg) {
			if ((*curorg)->winner) {
				cout << "WINNER IS #" << ((*curorg)->gnome)->genome_id << endl;
				//Prints the winner to file
				//IMPORTANT: This causes generational file output!
				print_Genome_tofile ((*curorg)->gnome, "xor_winner");
			}
		}

	}

	pop->epoch (generation);

	if (win) return 1;
	else return 0;

}

string IntToString (int i)
{
	stringstream ss;
	ss << i;
	return ss.str ();
}

std::string exec (const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::shared_ptr<FILE> pipe (_popen (cmd, "r"), _pclose);
	if (!pipe) throw std::runtime_error ("popen() failed!");
	while (!feof (pipe.get ())) {
		if (fgets (buffer.data (), 128, pipe.get ()) != NULL)
			result += buffer.data ();
	}
	return result;
}

void RunBot (string loc) {
	exec (("start python " + loc).c_str ());
}