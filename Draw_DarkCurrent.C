void Draw_DarkCurrent(){
  
  ifstream in;
  Double_t a,b,c,d;
  Int_t nli=81;
  TVectorD wl(nli);                                                                                                                                                                          
  TVectorD dcM(nli);
  in.open("../DIRC_Cookies_1116/dark_current_Sunday_11AM.txt");
  cout<<"Saturday 11AM"<<endl;
  in.open("dark_current_Saturday_11AM.txt");
  for(Int_t i=0; i<nli; i++){
    in >> a >> b >> c >> d;
    if(!in.good()) reak;
    wl[i] = a;
    dcM[i] = b;
    cout<<"wavelength  "<<wl[i]<<", dc = "<<dcM[i]<<endl;
  }
  in.close();

  TGraph* gdcM = new TGraph(wl, dcM);                                                                                                                                                           
  gdcM->SetLineWidth(2);                                                                                                                                                                        
  gdcM->SetLineColor(kGreen+2);                                                                                                                                                                 
  gdcM->SetTitle("");                                                                                                                                                                           
  gdcM->GetYaxis()->SetRangeUser(761.5, 764.2);                                                                                                                                                 
  gdcM->GetXaxis()->SetTitle("photon wavelength [nm]");                                                                                                                                         
  gdcM->GetYaxis()->SetTitle("dark current [nA]");                                                                                                                                             
                                                                                                                                                                                                
  TVectorD wl1(nli);                                                                                                                                                                            
  TVectorD dcE(nli);                                                                                                                                                                            
  in.open("../DIRC_Cookies_1116/dark_current_Saturday_8PM.txt");                                                                                                                                
  for(Int_t i=0; i<nli; i++){                                                                                                                                                                   
    in >> a >> b >> c >> d;                                                                                                                                                                     
    if(!in.good()) break;                                                                                                                                                                       
    wl1[i] = a;                                                                                                                                                                                 
    dcE[i] = b;                                                                                                                                                                                 
    cout<<"wavelength = "<<wl1[i]<<", dcE = "<<dcE[i]<<endl;                                                                                                                                    
  }                                                                                                                                                                                             
  in.close();                                                                                                                                                                                 
  
  TGraph* gdcE = new TGraph(wl1, dcE);                                                                                                                                      
  gdcE->SetLineWidth(2);                                                                                                                                                                     
  gdcE->SetLineColor(kBlue);

  TVectorD wl2(nli);                                                                                                                                                                         
  TVectorD dcS(nli);                                                                                                                                                                        
  in.open("../DIRC_Cookies_1116/dark_current_Sunday_4PM.txt");                                                                                                                               
  for(Int_t i=0; i<nli; i++){                                                                                                                                                                  
    in >> a >> b >> c >> d;                                                                                                                                                                     
    if(!in.good()) break;                                                                                                                                                                       
    wl2[i] = a;                                                                                                                                                                                 
    dcS[i] = b;                                                                                                                                                                                 
    cout<<"wavelength = "<<wl2[i]<<", dcS = "<<dcS[i]<<endl;                                                                                                                                   
  }                                                                                                                                                                                      
  in.close();                                                                                                                                                                               

  TGraph* gdcS = new TGraph(wl2, dcS);                                                                                                                                                         
  gdcS->SetLineWidth(2);                                                                                                                                                                      
  gdcS->SetLineColor(kRed);

  TCanvas* c1 = new TCanvas("c1","bilo",1200,800);
  gdcM->Draw("al");
  gdcE->Draw("samel");
  gdcS->Draw("samel");

  TLegend* leg = new TLegend(0.5,0.5,0.75,0.75);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->AddEntry(gdcM, "Saturday 11AM","l");
  leg->AddEntry(gdcE, "Saturday 8PM", "l");
  leg->AddEntry(gdcS, "Sunday 4PM","l");
  leg->Draw("same");
}
