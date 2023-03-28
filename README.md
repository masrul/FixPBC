# FixPBC: Make macromoleucle whole 
Most of the time typical PBC algorithm works to make a macromolecule whole. But, if macromolecule is very large and long, typical PBC does not work, as distance between centero of mass of molecule and end-atoms is larger than half of box length. Here, a new algorithm is devise to circumvent. PBC is applied bond-by-bond to reconstract whole molecule. Molecule is represented as graph, and traverse order is generated by using breadth first search.  

## Options

Options:
  -h,--help                   Print this help message and exit
  -f TEXT:FILE REQUIRED       trajectory file [XTC,GRO,TRR]
  -s TEXT:FILE REQUIRED       topology file [GRO]
  --sys-info TEXT:FILE REQUIRED
                              Molecule counts [ASCII FILE]
  --bond-ndx TEXT:FILE REQUIRED
                              bonds of molecule [ASCII FILE]
  --mol-id TEXT REQUIRED      ID of molecule
  --dt FLOAT                  analyzie every dt ps
  -b FLOAT                    Begin analysis
  -e FLOAT                    End analysis
  -o TEXT                     Output file [GRO]
  --max-frames INT            Maximum frames for analysis

## Installation
```bash 
git clone https://github.com/masrul/FixPBC/
cd FixPBC
mkdir build && cd FixPBC
cmake ..
make && make install
```