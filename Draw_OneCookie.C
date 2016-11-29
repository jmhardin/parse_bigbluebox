//void Draw_OneCookie(int N=10, int th=1, bool plot=false){
void Draw_OneCookie(bool plot=true){

  ifstream in;
  Double_t a,b,c,d;
const  Int_t nli=58;
  TVectorD wl(nli);                                                                                                                                  
  TVectorD tr1(nli);
  TVectorD tr2(nli);
  TVectorD tr3(nli);
  TVectorD tr4(nli);
  TVectorD tra(nli);
  TVectorD trey(nli);
  TVectorD trex(nli);
  TString infile;

  for(Int_t ix=1; ix<4; ix++){
    // infile.Form("../dc764/transmittance_cookie%d_%d_%d0.txt",N,th,ix);    
    infile.Form("../dc764/transmittance_cookief_%d0.txt",ix);
    cout<<"infile = "<<infile<<endl;
    in.open(infile);
    //    cout<<"cookie "<<N<<", point "<<ix<<endl;
    for(Int_t i=0; i<nli; i++){
      in >> a >> b;
      if(!in.good()) break;
      wl[i] = a;
      if(ix == 1){
	tr1[i] = b;
      }
      if(ix == 2){
	tr2[i] = b;
      }
      if(ix == 3){
	tr3[i] = b;
      }
    }
    in.close();   
  }

  TGraph* point1 = new TGraph(wl, tr1);
  TGraph* point2 = new TGraph(wl, tr2);
  TGraph* point3 = new TGraph(wl, tr3);

  /*if(N == 6 || 7 || 15){
    //    infile.Form("../dc764/transmittance_cookie%d_%d_00.txt",N,th);
    infile.Form("../dc764/transmittance_cookier_%d_00.txt",th);
    in.open(infile);
    for(Int_t i=0; i<nli; i++){
      in >> a >> b;
      if(!in.good()) break;
      wl[i] = a;
      tr4[i] = b;
    }
    in.close();

    TGraph* point4 = new TGraph(wl, tr4);
    point4->SetLineWidth(2);
    point4->SetLineColor(kOrange+2);
    }*/

  for(Int_t tri=0; tri<nli; tri++){
    tra[tri] = (tr1[tri] + tr2[tri] + tr3[tri])/3.;
    trey[tri] = sqrt((pow(tr1[tri]-tra[tri],2) + pow(tr2[tri]-tra[tri],2) + pow(tr3[tri]-tra[tri],2)) / 2.);
    trex[tri] = 0.;
    cout<<wl[tri]<<" "<<tra[tri]<<" "<<trey[tri]<<endl;
  }

  TGraphErrors* pointa = new TGraphErrors(wl, tra, trex, trey);
  pointa->SetLineColor(kRed);
  pointa->SetLineWidth(3);
  pointa->SetMarkerColor(kRed);
  pointa->SetMarkerStyle(20);
  pointa->SetFillColor(kRed);
  pointa->SetFillStyle(3002);

  //    point1->SetTitle(Form("cookie %d, thickness %d mm",N, th));
    point1->SetTitle(Form("cookie f, thickness 2 mm"));
    gStyle->SetTitleFont(40,"f");
  point1->GetXaxis()->SetTitle("wavelength [nm]");
  point1->GetYaxis()->SetTitle("transmittance");
  point1->GetXaxis()->SetTitleSize(0.05);
  point1->GetYaxis()->SetTitleSize(0.05);
  point1->GetXaxis()->SetLabelSize(0.05);
  point1->GetYaxis()->SetLabelSize(0.05);
  point1->SetLineWidth(2);
  point1->SetLineColor(kGreen+2);

  point2->SetLineWidth(2);
  point2->SetLineColor(kBlue);

  point3->SetLineWidth(2);
  point3->SetLineColor(kMagenta);

  if(plot){
    TCanvas* c1 = new TCanvas("c1",infile,1200,800);
    gPad->SetGridy();
    gPad->SetGridx();
    point1->Draw("al");
    point2->Draw("samel");
    point3->Draw("samel");
    pointa->Draw("same3l");
    /*    if(N == 6 || 7 || 15){
      point4->Draw("samel");
      }*/
    
    TLegend* leg = new TLegend(0.5,0.5,0.75,0.75);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.05);
    leg->AddEntry(point1, "x=0 mm","l");
    leg->AddEntry(point2, "x=10 mm", "l");
    leg->AddEntry(point3, "x=20 mm","l");
    /*    if(N == 6 || 15){
      leg->AddEntry(point4,"x=30 mm","l");
      }*/
    leg->Draw("same");
  }
  
}
