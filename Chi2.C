void Chi2()
{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1110);
  gStyle->SetOptFit(111); 
  //gStyle->SetPadGridX(1);
  //gStyle->SetPadGridY(1);
  gStyle->SetPalette(1);
  const int NBound = 51;
  const int NBins = 50;
  const double MassBoundaries[NBound] = {66.8014, 80.5137, 95.8941, 113.044, 132.071, 153.087, 176.208, 201.558, 229.267, 259.469, 
                                         292.306, 327.929, 366.493, 408.164, 453.112, 501.520, 553.576, 609.481, 669.442, 733.679, 
                                         802.422, 875.911, 954.400, 1038.15, 1127.45, 1222.58, 1323.84, 1431.57, 1546.09, 1667.76, 
                                         1796.95, 1934.03, 2079.43, 2233.55, 2396.86, 2569.81, 2752.89, 2946.61, 3151.52, 3368.16, 
                                         3597.14, 3839.07, 4094.59, 4364.38, 4649.15, 4949.64, 5266.64, 5600.94, 5953.41, 6324.94, 
                                         6716.47};

  const double bkg[NBins] = {736929,   479034,  59141.6, 30727.8, 134589,  8994.03, 5027.02, 3107.43, 1664.71,  1024.7,
                             31399.3,  20531.7, 12379.1, 8199.17, 4967.13, 3200.73, 2136.93, 53658.8, 34743.2,  22980.2,
                             14958.5,  10346.9, 6819.22, 48064.3, 31524.7, 22221.3, 14628.3, 10424.7, 6855.34,  4808.43,
                             3142.4,   2168.28, 1504.8,  971.011, 688.547, 439.375, 289.499, 193.462, 131.77,   80.5653,
                             51.3084,  32.4631, 19.2031, 11.8424, 7.58899, 4.06498, 2.37414, 1.14408, 0.586682, 0.258657};

  const double bkg10[NBins] = {736929,   479034,   59141.6,  30727.8,  134589,    8994.03,   5027.02,   3107.43,    1664.71,    1024.7,
                               31399.3,  20531.7,  12379.1,  8199.17,  4967.13,   3200.73,   2136.93,   5365.88,    3474.32,    2298.02,
                               1495.85,  1034.69,  681.922,  480.643,  315.247,   222.213,   146.283,   104.247,    68.5534,    48.0843,
                               31.424,   21.6828,  15.048,   9.71011,  6.88547,   4.39375,   2.89499,   1.93462,    1.3177,     0.805653,
                               0.513084, 0.324631, 0.192031, 0.118424, 0.0758899, 0.0406498, 0.0237414, 0.01114408, 0.00586682, 0.00258657};

  const double bkg100[NBins] = {736929,   479034,   59141.6,  30727.8,  134589,    8994.03,   5027.02,   3107.43,    1664.71,    1024.7,
                               31399.3,  20531.7,  12379.1,  8199.17,  4967.13,   3200.73,   2136.93,   53658.8,    34743.2,    22980.2,
                               14958.5,  10346.9,  6819.22,  4806.43,  3152.47,   2222.13,   1462.83,   1042.47,    685.534,    480.843,
                               314.24,   216.828,  150.48,   97.1011,  68.8547,   43.9375,   28.9499,   19.3462,    13.177,     8.05653,
                               5.13084, 3.24631, 1.92031, 1.18424, 0.758899, 0.406498, 0.237414, 0.1114408, 0.0586682, 0.0258657};  
   
  const double snl0[NBins] = {0, 0, 0, 0, 0, 0.374747, 0.0936867, 0.374747, 0.28106, 0.468433, 28.106,  32.7903, 81.9759, 100.713, 
                              140.53, 238.901, 332.588, 20892.1, 12460.3, 2623.23, 1498.99, 655.807, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  const double snl0_10[NBins] = {0, 0, 0, 0, 0, 0.374747, 0.0936867, 0.374747, 0.28106, 0.468433, 28.106, 32.7903, 81.9759, 100.713, 
                                 140.53, 238.901, 332.588, 2089.21, 1246.03, 262.323, 149.899, 65.5807, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  const double snl0_100[NBins] = {0, 0, 0, 0, 0, 0.374747, 0.0936867, 0.374747, 0.28106, 0.468433, 28.106, 32.7903, 81.9759, 100.713, 
                                  140.53, 238.901, 332.588, 20892.1, 12460.3, 2623.23, 1498.99, 655.807, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  
  const double snl1[NBins] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0588954, 0, 0, 10.6012, 2.35582, 3.53373, 0, 22.3803, 10.6012, 
                              353.373, 235.582, 388.71, 471.163, 1013, 1071.9, 2002.44, 1813.98, 906.99, 176.686, 58.8954, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  const double snl1_10[NBins] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0588954, 0, 0, 1.06012, 0.235582, 0.353373, 0, 2.23803, 1.06012, 
                                 3.53373, 2.35582, 3.8871, 4.71163, 10.13, 10.719, 20.0244, 18.1398, 9.0699, 1.76686, 0.588954, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  const double snl1_100[NBins] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0588954, 0, 0, 10.6012, 2.35582, 3.53373, 0, 22.3803, 10.6012, 
                                  35.3373, 23.5582, 38.871, 47.1163, 101.3, 107.19, 200.244, 181.398, 90.699, 17.6686, 5.88954, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  const double snl2[NBins] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.290504, 0.268157, 0.446929, 0.31285, 
                              0.268157, 0.31285, 0.290504, 0.379889, 0.424582, 0.424582, 0.424582,  0.558661, 0.826818, 0.782125, 1.00559, 1.34079,
                              2.07822, 4.69275, 2.5028, 0.469275, 0.0893857, 0, 0, 0};

  const double snl2_10[NBins] ={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.00290504, 0.00268157, 0.00446929,
                                0.0031285, 0.00268157, 0.0031285, 0.00290504, 0.00379889, 0.00424582, 0.00424582, 0.00424582, 0.00558661, 0.00826818,
                                0.00782125, 0.0100559, 0.0134079, 0.0207822, 0.0469275, 0.025028, 0.00469275, 0.000893857, 0, 0, 0};

  const double snl2_100[NBins] ={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0290504, 0.0268157, 0.0446929, 
                                0.031285, 0.0268157, 0.031285, 0.0290504, 0.0379889, 0.0424582, 0.0424582, 0.0424582, 0.0558661, 0.0826818, 0.0782125,
                                0.100559, 0.134079, 0.207822, 0.469275, 0.25028, 0.0469275, 0.00893857, 0, 0, 0};

  
  int bin,j,i;
  double snl[3][NBins];
  for(j=0;j<3;j++)
    {
      for(bin=0;bin<NBins;bin++)
        {
          if (j==0)
            snl[j][bin] = snl0_10[bin];
          if (j==1)
            snl[j][bin] = snl1_10[bin]; 
          if (j==2)
            snl[j][bin] = snl2_10[bin];
        }
    }
  double b;
  double s,x,p,sigma;
  int N=20000;
  int ndf[3];
  double events;
  char Resonance[3][100] = {"700","2000","5000"};
  char name[100];
  TH1F *hSign[3];
  TH1F *hProb[3];
  TH1F *hSigma[3];
  TRandom *rnd = new TRandom();
  rnd->SetSeed(0);
  TCanvas *c[3], *c1[3], *c2[3];
  double xl[3] = {0,0,0};
  double xh[3] = {9000,500,100};
  
  for(j=1;j<3;j++)
    {
      cout<<"Resonance: "<<Resonance[j]<<" GeV"<<endl;
      sprintf(name,"Resonance_%s_chi2",Resonance[j]);
      hSign[j] = new TH1F(name,name,500,xl[j],xh[j]);
      sprintf(name,"Resonance_%s_prob",Resonance[j]);
      hProb[j] = new TH1F(name,name,1000,0,1);
      sprintf(name,"Resonance_%s_sigma",Resonance[j]);
      hSigma[j] = new TH1F(name,name,100,0,10);
      for(i=0;i<N;i++)
        {
          x = 0.; 
          ndf[j] = 0; 
          for(bin=0;bin<NBins;bin++)
            {
              s = snl[j][bin];
              b = bkg10[bin];
              if (s>0 && b>0)
                {
                  ndf[j]++;
                  events = rnd->PoissonD(b+s);
                  x+ = pow(events-b,2)/b;
                }
             }
          p = TMath::Prob(x,ndf[j]); 
          sigma = sqrt(2.)*TMath::ErfInverse(1.-2.*p);
          hSign[j]->Fill(x);
          hProb[j]->Fill(p);
          hSigma[j]->Fill(sigma);
        }
    }// resonance loop
 
  for(j=1;j<3;j++)
    { 
      sprintf(name,"Resonance_%s_ch2_distribution",Resonance[j]); 
      c[j] = new TCanvas(name,name,900,600);
      hSign[j]->Scale(1./N);
      hSign[j]->Draw();
      sprintf(name,"Resonance: %s GeV",Resonance[j]);
      hSign[j]->SetTitle(name); 
      hSign[j]->GetXaxis()->SetTitle("#chi^{2}");
      hSign[j]->GetYaxis()->SetTitle("pdf");
      hSign[j]->GetYaxis()->SetTitleOffset(1.2);
      sprintf(name,"ndf = %d",ndf[j]);
      TPaveLabel *pave = new TPaveLabel(0.5,0.8,0.7,0.9,name,"NDC");
      pave->SetFillColor(0);
      pave->Draw(); 

      sprintf(name,"Resonance_%s_prob_distribution",Resonance[j]); 
      c1[j] = new TCanvas(name,name,900,600);
      hProb[j]->Scale(1./N);
      hProb[j]->Draw();
      sprintf(name,"Resonance: %s GeV",Resonance[j]);
      hProb[j]->SetTitle(name); 
      hProb[j]->GetXaxis()->SetTitle("p");
      hProb[j]->GetYaxis()->SetTitle("pdf");

      sprintf(name,"Resonance_%s_sigma_distribution",Resonance[j]); 
      c2[j] = new TCanvas(name,name,900,600);
      hSigma[j]->Scale(1./N);
      hSigma[j]->Draw();
      sprintf(name,"Resonance: %s GeV",Resonance[j]);
      hSigma[j]->SetTitle(name); 
      hSigma[j]->GetXaxis()->SetTitle("#sigma");
      hSigma[j]->GetYaxis()->SetTitle("pdf");

   }// resonance loop
}
