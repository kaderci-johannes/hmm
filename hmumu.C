#include <iostream>
string inpath = "/eos/user/a/amarini/Hmumu/fwk/2019_03_01_Hmm2018Sync_Feb15/";
string outpath = "~/Desktop/";

void hmumu()
{
Int_t mc, entries;
Float_t pt1;

TFile *file = new TFile;
TTree *hmm = new TTree;
TCanvas *c1 = new TCanvas;
TH1F *hist = new TH1F("hist","pt1",100,0.0,1000.0);

//c1->Divide(3,2);

//hist->Fill(.3);
//hist->Fill(.7);
//hist->Draw();

for(Int_t i=0; i<6; i++)
{
	file = TFile::Open(inpath+"ChHiggs_"+i+".root","READ");
	cout<<"File "<<i<<" opened."<<endl;
	hmm = (TTree*)file->Get("hmm");
	hmm->SetBranchAddress("mc",&mc);
	hmm->SetBranchAddress("pt1",&pt1);
	entries = hmm->GetEntries();
	for(Int_t j=0; j<entries; j++)
	{
		hmm->GetEntry(j);
		if(mc==20)
			hist->Fill(pt1);
	}

//	c1->cd(i+1)->SetLogy(1);
//	hmm->Draw("pt1","pt1<1000 && mc==20");
//	cout<<c1->IsDrawn()<<endl;
}
c1->cd();
hist->Draw();
c1->SaveAs("~/Desktop/pt1.pdf");
}
