#!/usr/bin/env python


import os,sys
import string, re
from time import gmtime, localtime, strftime


############################################################
dataFile2010 = "WmunuJets_ReReco_4_2_X_Data2010.root"
outputTextFile2010 = "Data_WmunuJJ_2010.txt"
    
dataFile2011 = "WmunuJets_Data2011_DCSmerged_571invpb.root"
outputTextFile2011 = "Data_WmunuJJ_2011.txt"

mcFileWJets = "WmunuJets_CMSSW415-Spring11MC_WJets.root"
outputTextFileWJets = "MC_WJets_WmunuJJ.txt"
    

mcFileWW = "WmunuJets_CMSSW415-Spring11MC_WWtoAnything.root"
outputTextFileWW = "MC_WW_WmunuJJ.txt"

mcFileWZ = "WmunuJets_CMSSW415-Spring11MC_WZtoAnything.root"
outputTextFileWZ = "MC_WZ_WmunuJJ.txt"

mcFileTT = "WmunuJets_CMSSW415-Spring11MC_TTToLNu2Q2B.root"
outputTextFileTT = "MC_TT_WmunuJJ.txt"
############################################################






def PrintToTextFile(inputRootFile, txtfilename):
    from ROOT import TTree, TFile, gROOT
    import re, array
    from array import array
    gROOT.Reset()
    f = TFile(inputRootFile,"read")
    tree = f.Get("WJet")

    entries = tree.GetEntriesFast()
    txtfile = file(txtfilename,"w")
    
    # loop over events
    for jentry in xrange( entries ):
        # get the next tree in the chain
        ientry = tree.LoadTree(jentry)
        #if ientry < 0 or ientry>120000:
        #    break

        # copy next entry into memory and verify
        nb = tree.GetEntry(jentry)
        if nb<=0:
            continue
        

        if not (tree.W_muon_pt>25.0 and (tree.W_muon_trackiso+tree.W_muon_ecaliso+tree.W_muon_hcaliso-tree.event_RhoForLeptonIsolation*3.141592653589*0.09)/tree.W_muon_pt < 0.1 and tree.W_muon_d0bsp<0.02 and tree.W_muon_d0bsp>-0.02 and tree.event_met_pfmet>25.0 and tree.W_mt>40.0 and tree.JetPFCor_Pt[0]>25.0 and tree.JetPFCor_Pt[1]>25.0):
            continue

        if jentry%50000 == 0:
            print "Processing entry = "+str(jentry)

        line = '%10.5f' %(-15) + " "+ '%10.5f' %(tree.W_muon_pt)+" "+ '%10.5f' %(tree.W_muon_eta) + ' ' + '%10.5f' %(tree.W_muon_phi) + ' ' + '%10.5f' %0  +  ' ' + '%10.5f' %0 + ' ' + '%10.5f' %0 + '\n'

        
        txtfile.write(line)
        line = '%10.5f'%(-5) + " " +'%10.5f' %(tree.event_met_pfmet)+' '+'%10.5f' %(tree.event_met_pfmetPhi)+' '+ '%10.5f' %(tree.event_met_pfmetsignificance)+' '+'%10.5f' %(tree.event_met_pfsumet) + ' ' + '%10.5f' %(tree.event_nPV) +' ' + '%10.5f'%0 +'\n'
        txtfile.write(line)
            
        numJets = 2
        if (tree.JetPFCor_Pt[2]>25.0 and tree.JetPFCor_Pt[3]<25.0):
            numJets = 3
        if (tree.JetPFCor_Pt[3]>25.0 and tree.JetPFCor_Pt[4]<25.0):
           numJets = 4
        if (tree.JetPFCor_Pt[4]>25.0 and tree.JetPFCor_Pt[5]>25.0):
           numJets = 5
        if (tree.JetPFCor_Pt[5]>25.0):
           numJets = 6

                 
        for iijet in xrange( numJets):
            line= '%10.5f' %(tree.JetPFCor_E[iijet]) +' '+'%10.5f' %(tree.JetPFCor_Pt[iijet])+''+'%10.5f' %(tree.JetPFCor_Eta[iijet])+' '+'%10.5f' %(tree.JetPFCor_Phi[iijet]) +' '+'%10.5f' %(tree.JetPFCor_bDiscriminator[iijet]) + ' ' + '%10.5f'%0 + ' ' + '%10.5f'%0
            txtfile.write(line+'\n')

    print "flat file "+txtfilename +" has been written."
    f.Close()


############################################################
PrintToTextFile(dataFile2010, outputTextFile2010 );   
PrintToTextFile(dataFile2011, outputTextFile2011 );
PrintToTextFile(mcFileWJets, outputTextFileWJets );
PrintToTextFile(mcFileWW, outputTextFileWW );
PrintToTextFile(mcFileWZ, outputTextFileWZ );
PrintToTextFile(mcFileTT, outputTextFileTT );
PrintToTextFile("WmunuJets_CMSSW415-Spring11MC_WWToLNuQQ_M-200.root", "MC_HWW_200GeV_WmunuJJ.txt")
PrintToTextFile("WmunuJets_CMSSW415-Spring11MC_WWToLNuQQ_M-250.root", "MC_HWW_250GeV_WmunuJJ.txt")
PrintToTextFile("WmunuJets_CMSSW415-Spring11MC_WWToLNuQQ_M-300.root", "MC_HWW_300GeV_WmunuJJ.txt")
PrintToTextFile("WmunuJets_CMSSW415-Spring11MC_WWToLNuQQ_M-350.root", "MC_HWW_350GeV_WmunuJJ.txt")
############################################################

