#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include "gmx_traj.hpp"
#include "timer.hpp"
#include "CLI11.hpp"
#include "str_util.hpp"
#include "traj_writer.hpp"
#include "pbc_util.hpp"

using std::fixed;
using std::setprecision;
using std::setw;
using std::right;

// Global varible 
std::string cmd{""};
 
class FixPBC {
public:
    GMXTraj& traj;
    size_t nFrames=0;
    size_t mol_id;

    FixPBC(GMXTraj& _traj,size_t _mol_id, std::string _bond_ndx_file, std::string _out_file):
        traj{_traj},
        mol_id{_mol_id},
        bond_ndx_file{_bond_ndx_file}
    {
        read_bond_ndx();
        outFH.open(_out_file);
    };


    void run(){
        nFrames +=1;

        // Fix broken  
        PBCUtil::make_whole(traj,mol_id,bonds);

        // Write 
        write_frame(traj,outFH);

    } 

    ~FixPBC(){
        outFH.close();
    }

private: 
    std::string bond_ndx_file;
    std::vector<std::vector<size_t>> bonds; 
    std::ofstream outFH;
    std::vector<size_t> out_index; 

    void read_bond_ndx(){
        std::ifstream FH(bond_ndx_file);
        std::string line; 
        
        // Ignoring first line 
        getline(FH,line);
        while (std::getline(FH, line)){
            auto bond = StrUtil::extract_numbers(line);
            // to 0 based indexing 
            for (auto& item : bond)
                --item; 
            bonds.push_back(bond);
        }
        FH.close();
    }

};


int main(int argc, char* argv[]){  
    Timer timer{};
    std::string top_file{""};
    std::string traj_file{""};
    std::string sys_info{""};
    std::string bond_ndx{""};
    std::string out_file{"out.gro"};
    float dt =1.0;
    float begin = 0.0;
    float end = std::numeric_limits<float>::max();   
    int max_frames = std::numeric_limits<int>::max();  
    size_t mol_id=-1; 

    CLI::App app{"Fix PBC of macromolecule"};
    app.add_option("-f",traj_file,"trajectory file [XTC,GRO,TRR]")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("-s",top_file,"topology file [GRO]")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--sys-info",sys_info,"Molecule counts [ASCII FILE]")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--bond-ndx",bond_ndx,"bonds of molecule [ASCII FILE]")
        ->required()
        ->check(CLI::ExistingFile);
    app.add_option("--mol-id",bond_ndx,"ID of molecule")
        ->required();
    app.add_option("--dt",dt,"analyzie every dt ps");
    app.add_option("-b",begin,"Begin analysis");
    app.add_option("-e",end,"End analysis");
    app.add_option("-o",out_file,"Output file [GRO]");
    app.add_option("--max-frames",max_frames,"Maximum frames for analysis");
    CLI11_PARSE(app, argc, argv);
    
    // Commad used in analysis, for future references 
    for (int i=0; i<argc;++i)
        cmd += (" " + std::string {argv[i]});


    // Create trajectory 
    GMXTraj traj{traj_file,top_file};
    traj.create_molecule_tracker(sys_info);

    // Traverse trajectory and do analysis 
    FixPBC analysis(traj,mol_id,bond_ndx,out_file);
    int nFrames=0; 
    float tol =0.00001; // tolarance for fmod
    while(traj.next()){
        if (nFrames >= max_frames || traj.time > end) break;
        if (traj.time < begin || std::fmod(traj.time,dt)>tol) continue; 
        
        std::cout << "Time: "<<traj.time <<"\n";
        analysis.run();
        ++nFrames;
    }


    // Print elapsed time 
    timer.print_elapsed_time();
    
    return 0;
}
 
