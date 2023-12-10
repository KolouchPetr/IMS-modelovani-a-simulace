out_text = ""
for geom in self.cLayer.getFeatures():
    out_text += str(geom.attribute(selFeatures[0].fieldNameIndex(cField)))
    for f in self.cLayer.getFeatures():
        if f != geom:
            if (geom.geometry().touches(f.geometry()) == True):
                out_text += ", "
                out_text += f[cField]
    out_text += "\n"

self.dlg.txtNeighborhood.appendPlainText(out_text)