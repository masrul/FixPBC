/**
 * @author      : Masrul Huda (mail2masrul@gmail.com)
 * @file        : traj_writer
 * @created     : Tuesday Oct 11, 2022 11:42:23 CDT
 */

#ifndef TRAJ_WRITER_HPP

#define TRAJ_WRITER_HPP

#include "gmx_traj.hpp"
#include <fstream>
#include <iomanip>

using std::fixed;
using std::setprecision;
using std::setw;
using std::right;
using std::left;

void write_frame(const GMXTraj& traj, std::ofstream& FH){
    FH<<"t="<<traj.time<<"\n";
    FH<<setw(10)<<left<<traj.natoms<<"\n";

    for (size_t i=0; i<traj.natoms; ++i){
        auto atomID = i+1;
        FH<<setw(5)<<right<<traj.resids[i]
          <<setw(5)<<right<<traj.resnames[i]
          <<setw(5)<<right<<traj.symbols[i]
          <<setw(5)<<right<<atomID
          <<fixed<<setw(8)<<setprecision(3)<<right <<traj.pos[i][0]
          <<fixed<<setw(8)<<setprecision(3)<<right <<traj.pos[i][1]
          <<fixed<<setw(8)<<setprecision(3)<<right <<traj.pos[i][2]
          <<"\n";
    }
    FH<<fixed<<setw(10)<<setprecision(5)<<right<<traj.lx
      <<fixed<<setw(10)<<setprecision(5)<<right<<traj.ly
      <<fixed<<setw(10)<<setprecision(5)<<right<<traj.lz
      <<"\n";
}


void write_frame(const GMXTraj& traj,const std::vector<size_t>index, std::ofstream& FH){
    FH<<"t= "<<traj.time<<"\n";
    FH<<setw(10)<<left<<index.size()<<"\n";
    
    size_t atomID = 0;
    for (size_t i : index){
        ++atomID;
        FH<<setw(5)<<right<<traj.resids[i]
          <<setw(5)<<right<<traj.resnames[i]
          <<setw(5)<<right<<traj.symbols[i]
          <<setw(5)<<right<<atomID
          <<fixed<<setw(8)<<setprecision(3)<<right <<traj.pos[i][0]
          <<fixed<<setw(8)<<setprecision(3)<<right <<traj.pos[i][1]
          <<fixed<<setw(8)<<setprecision(3)<<right <<traj.pos[i][2]
          <<"\n";
    }
    FH<<fixed<<setw(10)<<setprecision(5)<<right<<traj.lx
      <<fixed<<setw(10)<<setprecision(5)<<right<<traj.ly
      <<fixed<<setw(10)<<setprecision(5)<<right<<traj.lz
      <<"\n";
}

#endif /* end of include guard TRAJ_WRITER_HPP */

