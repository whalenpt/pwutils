
#ifndef REPORT_HELPER_H_
#define REPORT_HELPER_H_

#include <vector>
#include <map>
#include "pwconstants.h"

namespace pw{

const int REPORT_PRECISION = 16;
const int REPORT_PADING = 8;
using metadataMap = std::map<std::string,std::string>;
using metadataPair = std::pair<std::string,std::string>;

void getPhaseLimits(std::vector<double>& in,int& stindx,int& endindx,int sz);
bool CheckSignChange(std::vector<double>& in,int indx1,int indx2);
void AdjustPhase(std::vector<double>& in,int sz);
int ComputeOutN_2D(int nD,int stride);

}

#endif

