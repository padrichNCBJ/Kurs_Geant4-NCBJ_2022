# -*- coding: UTF-8 -*-

# Jak to uruchomic? 
# python3 ntuple_plot.py

from ROOT import TCanvas, TPad, TFile
from ROOT import gStyle, gROOT

f1 = TFile('Generator_Test.root')
ntuple = gROOT.FindObject('Generator')

c1 = TCanvas('c1','The Ntuple canvas',200,10,700,780)

# Inside this canvas, we create 4 pads
pad1 = TPad('pad1','This is pad1',0.02,0.52,0.48,0.98,21)
pad2 = TPad('pad2','This is pad2',0.52,0.52,0.98,0.98,21)
pad3 = TPad('pad3','This is pad3',0.02,0.02,0.48,0.48,21)
pad4 = TPad('pad4','This is pad4',0.52,0.02,0.98,0.48,1)
pad1.Draw()
pad2.Draw()
pad3.Draw()
pad4.Draw()

# Change default style for the statistics box
gStyle.SetStatW(0.30)
gStyle.SetStatH(0.20)
gStyle.SetStatColor(42)

pad1.cd()
pad1.SetGrid()
ntuple.SetLineColor(1)
ntuple.SetFillStyle(1001)
ntuple.SetFillColor(45)
ntuple.Draw('Ekin')
c1.Update()

pad2.cd()
pad2.SetGrid()
#pad2.SetLogy()
pad2.GetFrame().SetFillColor(15)
ntuple.SetLineColor(1)
ntuple.SetFillStyle(1001)
ntuple.SetFillColor(45)
ntuple.Draw('PDG')
c1.Update()

pad3.cd()
pad3.SetGrid()
#pad2.SetLogy()
pad2.GetFrame().SetFillColor(15)
ntuple.SetLineColor(1)
ntuple.SetFillStyle(1001)
ntuple.SetFillColor(45)
ntuple.Draw('y:x')
c1.Update()

pad4.cd()
pad4.SetGrid()
#pad2.SetLogy()
pad2.GetFrame().SetFillColor(15)
ntuple.SetLineColor(1)
ntuple.SetFillStyle(1001)
ntuple.SetFillColor(45)
ntuple.Draw('x', 'x>0')
c1.Update()


c1.cd()
c1.Update()

w = input('Nacisnij dowolny klawisz by wyjsc \n')


