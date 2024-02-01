#ifndef GENES_H
#define GENES_H
//-----------------------------------------------------------------------
//
//  Name: GeneGenes.h
//
//  Author: Mat Buckland 2002 (fup@btinternet.com)
//
//	Desc: neuron and link gene definitions used in the 
//        implementation of Kenneth Owen Stanley's and Risto 
//        Miikkulainen's NEAT idea.These structures are used to define
//        a genome.
//
//-----------------------------------------------------------------------

class CNeuron;

//------------------------------------------------------------------------
//
//  enumeration for all the available neuron types
//------------------------------------------------------------------------
enum neuron_type
{
  input,
  hidden,
  output,
  bias,
  none
};

//------------------------------------------------------------------------
//
//  this structure defines a neuron gene
//------------------------------------------------------------------------
struct SNeuronGene
{  
  //its identification
  int         iID;

  //its type
  neuron_type NeuronType;

  //is it recurrent
  bool        bRecurrent;

  //sets the curvature of the sigmoid function
  double    dActivationResponse;

  //position in network grid
  double    dSplitY, dSplitX;

  SNeuronGene(neuron_type type,
              int         id,
              double      splitY,
              double      splitX,
              bool        r = false,
              double      act = 1):iID(id),
                                   NeuronType(type),
                                   bRecurrent(r),
                                   dSplitY(splitY),
                                   dSplitX(splitX),
                                   dActivationResponse(act)
  {}

  //overload << for streaming
  friend ostream& operator <<(ostream &os, const SNeuronGene &rhs)
  {
    os << "\nNeuron: " << rhs.iID << "  Type: " << rhs.NeuronType
       << "  Recurrent: " << rhs.bRecurrent << "  Activation: " << rhs.dActivationResponse
       << "  SplitX: " << rhs.dSplitX << "  SplitY: " << rhs.dSplitY;
    
    return os;
  }

  
};

//------------------------------------------------------------------------
//
//  this structure defines a link gene
//------------------------------------------------------------------------
struct SLinkGene
{
	//the IDs of the two neurons this link connects		
	int     FromNeuron,
	        ToNeuron;
	
	double	dWeight;

  //flag to indicate if this link is currently enabled or not
  bool    bEnabled;

  //flag to indicate if this link is recurrent or not
  bool    bRecurrent;
	
	int     InnovationID;

  SLinkGene(){}
  
  SLinkGene(int    in,
            int    out,
            bool   enable,
            int    tag,
            double weight,
            bool   rec = false):bEnabled(enable),
								                InnovationID(tag),
                                FromNeuron(in),
                                ToNeuron(out),
                                dWeight(weight),
                                bRecurrent(rec)
	{}

  //overload '<' used for sorting(we use the innovation ID as the criteria)
	friend bool operator<(const SLinkGene& lhs, const SLinkGene& rhs)
	{
		return (lhs.InnovationID < rhs.InnovationID);
	}

  //overload << for streaming
  friend ostream& operator <<(ostream &os, const SLinkGene &rhs)
  {
    os << "\nInnovID: " << rhs.InnovationID << "  From: " << rhs.FromNeuron
       << "  To: " << rhs.ToNeuron << "  Enabled: " << rhs.bEnabled 
       << "  Recurrent: " << rhs.bRecurrent << "  Weight: " << rhs.dWeight;

    return os;
  }
};


                                         
#endif 