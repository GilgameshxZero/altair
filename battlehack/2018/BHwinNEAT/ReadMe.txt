This distribution contains a Microsoft Windows implementation of the 
NeuroEvolution of Augmenting Topologies (NEAT) method for evolving 
neural network topologies and weights.  In this release,
NEAT is applied to a "minesweepers" task in which the goal is
to explore as much terrain as possible in a finite amount of time.

-The complete source code in this distribution was written by Mat Buckland,
 whose site is:
 http://www.ai-junkie.com/

-The NEAT method was developed by Kenneth Stanley.  Additional information
 and papers describing NEAT in detail can be found at his website:
 http://www.cs.utexas.edu/users/kstanley/

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as published
by the Free Software Foundation. This program is distributed in the hope
that it will be useful, but without any warranty; without even the implied 
warranty of merchantability or fitness for a particular purpose. See the GNU 
General Public License for more details.

We hope that this software will be a useful starting point for your own
explorations in neuroevolution. The software is provided as is,
however, we will do our best to maintain it and accommodate
suggestions. If you want to be notified of future releases of the
software or have questions, comments, bug reports or suggestions
related to the software or source code itself, send
email to fup@btinternet.com.  For general questions about NEAT,
send e-mail to kstanley@cs.utexas.edu, or refer to the NEAT
User's Page and FAQ at http://www.cs.utexas.edu/users/kstanley/neat.html.

NOTES:

/* Executable */

A ready-to-run executable is available in the "executable" folder.
It also has a companion parameter file.

/* Compiling */

The source code is included as a Microsoft Visual C++ project.
You can use that system to compile.  However, if you just want
to play with the demo, the executable should work as-is without
recompiling.

/* Parameters */

You can change the task by changing the parameters in params.ini.
For example, you can make the scale larger or smaller, change the sensor
ranges, number of sensors, size of sweepers, etc...
NEAT evolution parameters can also be changed in params.ini.

Note that iNumTicks is the duration of a generation.  The more ticks,
the more time there is to explore.  If sweepers become perfect at
exploring as much ground as possible in a given number of ticks,
the only way to get them to explore more is to try evolving
with a higher number of ticks (assuming other parameters are kept constant).

/* Keys /*


F - Toggles Fast Mode.  In fast mode, runs as fast as possible, shows stats.
     In viewing mode, it shows the sweepers themselves playing.

B - When not in fast mode, toggles between observing the best performers only,
     and viewing all sweepers in the population simultaneously.   

R - Reset and run

Numbers 1 through 4 - When viewing the best sweepers, a path is shown of
  every place visited by one of the four best.  You can switch which path
  you want to see by pressing number 1,2,3, or 4.


/* The Phenotype Display */

Excitory forward connections are shown in gray and inhibitory forward connections are shown in yellow.

Excitory recurrent connections are shown in red and inhibitory connections are shown in blue.

Any connections from the bias neuron are shown in green.

The thickness of the line gives an indication of the magnitude of the connection weight.

The inputs include 2 inputs for each sensor: one to detect walls and one to detect
  paths already covered.  Finally, there is a collision detector input and a bias input.

/* Outputting Information */


There is some debugging stuff in the classes so you can output genome/species/innovation information.

In Cga::Epoch you will find some lines you can uncomment to output the innovation and species info for the current generation.



/* Saving and using a successful genome */

Once you have evolved a successful genome, you can save it to a file using Cga::WriteGenome. To use it at a later date, create a CGenome object then call the CGenome::CreateFromFile method. Like this:

CGenome MyGenome;

MyGenome.CreateFromFile("MyGenomesFilename.txt");

All you have to do now to set up the phenotype is:

CNeuralNet* MyNetwork = MyGenome.CreatePhenotype();

and away you go. 



/* General Info */


If  want to set a maximum for the number of species created assign a value to iMaxNumberOfSpecies 'params.ini'. The program will then try and do its best to keep the number of species between 2 and the max.




