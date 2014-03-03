/*****************************************************************************
 * Project: RooFit                                                           
 * Package: BToDKTo3piK                                                     
 *    File: $Id: BdkDalitzSmear.cc,v 1.1 2006/03/20 19:04:31 fwinkl Exp $
 * Authors:                                                                  
 *   Frank Winklmeier, Colorado State University                             
 * Description:                                                              
 *   Class to smear a N-dim RooAbsPdf with M (M<=N) resolution PDFs          
 *   BdkDalitzSmear is not a fully functional RooAbsPdf itself.                    
 *   Only generate() can be used on it. I.e. does not support fitting.       
 *                                                                           
 * Copyright (c) 2006, Colorado State University                             
 *****************************************************************************/

#include "RooFitCore/RooFit.hh"

#include "Riostream.h"

#include "BToDKTo3piK/BdkDalitzSmear.hh"

#include "RooFitCore/RooAbsReal.hh"
#include "RooFitCore/RooRealVar.hh"
#include "RooFitCore/RooDataSet.hh"
#include "RooFitCore/RooGenContext.hh"


using namespace std;

ClassImp(BdkDalitzSmear)

/// Constructor
/// Smear (convolute) m12/m13 generated by pdf with the resolutions models
BdkDalitzSmear::BdkDalitzSmear(const char *name, const char *title,
                               BdkDalitzBase& pdf,
                               RooAbsPdf& res12, RooAbsPdf& res13,
                               RooAbsReal& m12, RooAbsReal& m13) :
  BdkDalitzBase(name,title),
  _pdf("pdf","original PDF",this,pdf),
  _resModels("resModels","proxy list of resolution models",this),
  _resVars("resVars","proxy list of resolution variables",this)
{
  init();
  setEventBuffer();

  RooArgList resModels(res12,res13);
  RooArgList resVars(m12,m13);
  
  // Do some basic checks
  
  for (Int_t i=0; i<resModels.getSize(); i++) {
    if (!((RooAbsPdf&)resModels[i]).getParameters(RooArgSet())->contains(resVars[i])) {
      cout << "BdkDalitzSmear::BdkDalitzSmear(" << GetName()
	   << ") pdf " << resModels[i].GetName()
	   << " does not depend on "<<resVars[i].GetName() << " Ignored."
	   <<endl;
      continue;
    }
    _resModels.add(resModels[i]);
    _resVars.add(resVars[i]);
  }
}

/// Copy constructor
BdkDalitzSmear::BdkDalitzSmear(const BdkDalitzSmear& other, const char* name) : 
  BdkDalitzBase(other,name),
  _pdf("pdf",this,other._pdf),
  _resModels("resModels",this,other._resModels),
  _resVars("resVars",this,other._resVars),
  _events(other._events)
{
  init();
}

/// Destructor
BdkDalitzSmear::~BdkDalitzSmear()
{
  clearEventBuffer();
}

void BdkDalitzSmear::init()
{
  _pdfData = 0;
  _pdfEventsUsed = 0;
  clearEventBuffer();
}

void BdkDalitzSmear::clearEventBuffer()
{
  // Clean up old datasets
  delete _pdfData;
  _pdfData = 0;
  _pdfEventsUsed = 0;
  
  for (Int_t i=0; i<_resData.size(); i++) delete _resData[i];
  _resData.clear();
  _resEventsUsed.clear();

  // Initialize empty datasets
  _resData.insert(_resData.begin(),_resModels.getSize(),(RooDataSet*)0);
  _resEventsUsed.insert(_resEventsUsed.begin(),_resModels.getSize(),0);
}


/// Not supported by this PDF. Always returns 1.
Double_t BdkDalitzSmear::evaluate() const
{
  return 1;
}


/// Get generator context
RooAbsGenContext*
BdkDalitzSmear::genContext(const RooArgSet &vars, const RooDataSet *prototype, 
                           const RooArgSet* auxProto, Bool_t verbose) const 
{
  return new RooGenContext(*this,vars,prototype,auxProto,verbose,
			   (RooArgSet*)&_resVars) ;
  //                                     ^^^^^^
  //     This forces that our own generator is used for these variables
}


Int_t BdkDalitzSmear::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) const
{
  if (matchArgs(directVars,generateVars,_resVars)) return 1 ;  
  return 0;
}


/// This gets called by RooAbsPdf::generate()
void BdkDalitzSmear::initGenerator(Int_t code)
{
  assert(code==1);
  clearEventBuffer();
}


/// Get PDF data from event buffer
RooArgSet BdkDalitzSmear::getPdfData()
{
  // generate PDF data if needed
  if (_pdfData==0 || _pdfEventsUsed >= _pdfData->numEntries()) {
    delete _pdfData;    
    _pdfData = ((RooAbsPdf*)_pdf.absArg())->generate(_resVars,_events);    
    _pdfEventsUsed = 0;
  }
   // get one entry from the PDF dataset
  RooArgSet vars(*_pdfData->get(_pdfEventsUsed++));

  return vars;
}


/// Get resolution data from event buffer
RooArgList BdkDalitzSmear::getResolutionData()
{
  RooArgList resVals;
  for (Int_t i=0; i<_resVars.getSize(); i++) {
    // generate resolution data if needed
    if (_resData[i]==0 || _resEventsUsed[i] >= _resData[i]->numEntries()) {
      delete _resData[i];
      _resData[i] = ((RooAbsPdf&)_resModels[i]).generate(_resVars[i],_events);
      _resEventsUsed[i] = 0;
      }
    
    // get one entry from resolution dataset
    resVals.add(*_resData[i]->get(_resEventsUsed[i]++)->first());
  }
  return resVals;
}


/// Our own generator
void BdkDalitzSmear::generateEvent(Int_t code)
{
  assert(code==1) ;

  // We need to do this until the smeared value is inside the Dalitz plot
  while (1) {

    // Original PDF value
    RooArgSet vars = getPdfData();
    Double_t m12Val =((RooRealVar*) vars.find(_resVars[0].GetName()))->getVal();
    Double_t m13Val =((RooRealVar*) vars.find(_resVars[1].GetName()))->getVal();

    // smear the value
    RooArgList resVals = getResolutionData();

    Double_t m12smear = m12Val + ((RooRealVar&)resVals[0]).getVal();
    Double_t m13smear = m13Val + ((RooRealVar&)resVals[1]).getVal();
    
    if (inDalitz(m12smear,m13smear)) {
      ((RooRealVar&)_resVars[0]).setVal(m12smear);
      ((RooRealVar&)_resVars[1]).setVal(m13smear);
      break;
    }
  }
}


