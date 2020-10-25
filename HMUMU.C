#include <iostream>
#include <TLorentzVector.h>

// mc=10: M>50 (DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM)
// mc=11: 105<M<160 (DYJetsToLL_M-105To160_TuneCP5_PSweights_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM)

void HMUMU(const int N){

gROOT->SetBatch(kTRUE);

char path[1024], outpath[1024];
TLorentzVector u1,u2;
//Int_t err=0;

TFile *file = new TFile;
TFile *out = new TFile("./results.root","recreate");
TTree *hmm = new TTree;

TCanvas *c1 = new TCanvas;
TCanvas *c2 = new TCanvas;
TCanvas *c3 = new TCanvas;
TCanvas *c4 = new TCanvas;
TCanvas *c5 = new TCanvas;
TCanvas *c6 = new TCanvas;

TH1F *h10 = new TH1F("mc = 10","mc = 10",100,70,170);
TH1F *h11 = new TH1F("mc = 11","mc = 11",100,70,170);
TH1F *h120gev = new TH1F("m = 120","m = 120",100,70,170);
TH1F *h125gev = new TH1F("m = 125","m = 125",100,70,170);
TH1F *h130gev = new TH1F("m = 130","m = 130",100,70,170);
TH1F *h00 = new TH1F("mc != 0, 10, 11","mc != 0, 10, 11",100,70,170);

for(Int_t i=0; i<N; i++)
{
	sprintf(path,"/eos/user/a/amarini/Hmumu/fwk/2019_03_01_Hmm2018Sync_Feb15/ChHiggs_%i.root",i);
	file = TFile::Open(path,"READ");
	if(file==nullptr){
		cout<<endl<<"### Error in file "<<i<<", skipping. ###"<<endl<<endl;
		continue;
	}
	cout<<"File "<<"ChHiggs_"<<i<<".root"<<" opened."<<endl;
	hmm = (TTree*)file->Get("hmm");

	TTreeReader hmm_r(hmm);
	TTreeReaderValue<Int_t> mc(hmm_r, "mc");
	TTreeReaderValue<Float_t> pt1(hmm_r,"pt1");
	TTreeReaderValue<Float_t> pt2(hmm_r,"pt2");
	TTreeReaderValue<Float_t> eta1(hmm_r,"eta1");
	TTreeReaderValue<Float_t> eta2(hmm_r,"eta2");
	TTreeReaderValue<Float_t> phi1(hmm_r,"phi1");
	TTreeReaderValue<Float_t> phi2(hmm_r,"phi2");
	TTreeReaderValue<Float_t> mass(hmm_r,"mass");
	TTreeReaderValue<Double_t> weight(hmm_r,"weight");
	while(hmm_r.Next())
	{
		u1.SetPtEtaPhiM(*pt1,*eta1,*phi1,.105658);
		u2.SetPtEtaPhiM(*pt2,*eta2,*phi2,.105658);
		if(*mc==10/* && (u1+u2).M()<1000. && (u1+u2).M()>0.*/) h10->Fill((u1+u2).M(),(*weight)*60000);
		else if(*mc==11/* && (u1+u2).M()<1000. && (u1+u2).M()>0.*/) h11->Fill((u1+u2).M(),(*weight)*60000);
		else if(*mc%10==-1/* && (u1+u2).M()<1000. && (u1+u2).M()>0.*/) h120gev->Fill((u1+u2).M(),(*weight)*60000);
		else if(*mc%10==-2/* && (u1+u2).M()<1000. && (u1+u2).M()>0.*/) h125gev->Fill((u1+u2).M(),(*weight)*60000);
		else if(*mc%10==-3/* && (u1+u2).M()<1000. && (u1+u2).M()>0.*/) h130gev->Fill((u1+u2).M(),(*weight)*60000);
		else if(*mc) h00->Fill((u1+u2).M(),(*weight)*60000);
	}
}
out->cd();
h10->SetXTitle("M (GeV)");
h10->Write();
h11->SetXTitle("M (GeV)");
h11->Write();
h00->SetXTitle("M (GeV)");
h00->Write();
h120gev->SetXTitle("M (GeV)");
h120gev->Write();
h125gev->SetXTitle("M (GeV)");
h125gev->Write();
h130gev->SetXTitle("M (GeV)");
h130gev->Write();
out->Write();
out->Close();

c1->cd();
h10->Draw();
c2->cd();
h11->Draw();
c3->cd();
h00->Draw();
c4->cd();
h120gev->Draw();
c5->cd();
h125gev->Draw();
c6->cd();
h130gev->Draw();

c1->SetLogy(1);
c2->SetLogy(1);
c3->SetLogy(1);
c4->SetLogy(1);
c5->SetLogy(1);
c6->SetLogy(1);

sprintf(outpath,"~/Desktop/mc10.png");
c1->SaveAs(outpath);
sprintf(outpath,"~/Desktop/mc11.png");
c2->SaveAs(outpath);
sprintf(outpath,"~/Desktop/neither.png");
c3->SaveAs(outpath);
sprintf(outpath,"~/Desktop/mcn120.png");
c4->SaveAs(outpath);
sprintf(outpath,"~/Desktop/mcn125.png");
c5->SaveAs(outpath);
sprintf(outpath,"~/Desktop/mcn130.png");
c6->SaveAs(outpath);
}
