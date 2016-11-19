#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(int nvars, char** vars)
{
	
	double dark_current = 739.4; //nA
	double min_wavelength = 314;
	bool return_integral = false;
	int open_file_ind = 2;
	if (nvars == 1)
	{
		printf("use -h for usage\n");
		return -1;
	}
	for (int i = 1; i < nvars; i++)
	{
		if (strcmp(vars[i],"-integrate") == 0)
		{
			return_integral = true;
		}
		else if (strcmp(vars[i],"-ifile") == 0)
		{
			//I'm sorry about this
			i++;
			open_file_ind = i;
		}
		else if (strcmp(vars[i],"-dark_current") == 0)
		{
			i++;
			dark_current = atof(vars[i]);
		}
		else
		{
			printf("Usage: parse_transmittance -ifile <data_file>\n");
			printf("Outputs a 2 column list of wavelengths and reflectances.  Expects the files to have 3 columns - wavelength, reference, signal.\n");
			printf("Usage: parse_reflectance -integrate -ifile <data_file>\n");
			printf("Returns a single number corresponding to the average reflectance weighted by the Cernkov spectrum and PMT QE\n");
			printf("ending....\n");
			return -1;
		}
	}

	

	if (nvars == 3 && strcmp(vars[1],"-integrate") == 0)
	{
		return_integral = true;
		//Forst index was the flag
		open_file_ind++;
	}

	ifstream data_file(vars[open_file_ind]);
	
	if (!(data_file.is_open()))
	{
		printf("Failing... Unable to open file: %s\n",vars[open_file_ind]);
	}

	string tmp_data_line;
	//ignore first 2 lines of each
	getline(data_file,tmp_data_line);
	getline(data_file,tmp_data_line);

	

	vector<double> ref_wavelengths;
	vector<double> ref_currents;
	vector<double> data_wavelengths;
	vector<double> data_currents;

	while (getline(data_file,tmp_data_line))
	{
		double tmp_wl = -1;
		double tmp_ref_current = -1;
		double tmp_data_current = -1;
        	stringstream strstr(tmp_data_line);
		strstr >> tmp_wl;
		strstr >> tmp_ref_current;
		strstr >> tmp_data_current;
		ref_wavelengths.push_back(tmp_wl);
		data_wavelengths.push_back(tmp_wl);
		ref_currents.push_back(tmp_ref_current);
		data_currents.push_back(tmp_data_current);
    	}

	vector<double> reflect_wavelengths;
	vector<double> reflect_reflectance;
//	dark_current = ref_currents[0];
	for (unsigned int i = 0; i < ref_wavelengths.size(); i++)
	{
		double tmp_reflectance = -1;
		if (ref_wavelengths[i] != data_wavelengths[i])
		{
			cerr << "mismatch between wavelengths in 2 files - Error\n" << endl;
		}
		tmp_reflectance = (data_currents[i] - dark_current)/(ref_currents[i] - dark_current);
		reflect_wavelengths.push_back(ref_wavelengths[i]);
		reflect_reflectance.push_back(tmp_reflectance);
		if (reflect_wavelengths[i] > min_wavelength && return_integral == false)
		{
			printf("%12.04f %12.04f\n",reflect_wavelengths[i],tmp_reflectance);
		}
	}

	if (return_integral == true)
	{
		double min_QE = 300;
		double max_QE = 600;
		int n_QE = 31;
		double t_QE[31] = {\
			0.016415, 0.074064, 0.141658, 0.184219, 0.20634,  0.217191, 0.223244,
              	 	0.222296, 0.215232, 0.206302, 0.195574, 0.183007, 0.169403, 0.155447,
               		0.140014, 0.127696, 0.115716, 0.104086, 0.092256, 0.084083, 0.075418,
               		0.067311, 0.060243, 0.053588, 0.047765, 0.04344,  0.037999, 0.034177,
               		0.030869, 0.027848, 0.024141
        	};

		double norm_QE = 0;
		double tmp_wl = -1;
		double sep_QE = ((max_QE - min_QE))/(n_QE - 1);

		double reflectance_integrated = 0;

		bool output_all_refl_spec = true;

		for (unsigned int i = 0; i < reflect_wavelengths.size(); i++)
		{
			if (reflect_wavelengths[i] < min_wavelength)
			{
				continue;
			}

			double tmp_lam = reflect_wavelengths[i];

	                //Ignoring that the QE points are right on multiples of 10.  Assuming they are for speed.
	                //This may not be neccessary, but I doubt it matters.
	                int ind_QE = (tmp_lam - min_QE + .01)/sep_QE;

	                double above_ind = tmp_lam - (min_QE + sep_QE*ind_QE);
			double tmp_QE_val = t_QE[ind_QE]*(sep_QE-above_ind)/sep_QE + t_QE[ind_QE+1]*above_ind/sep_QE;

			//printf("%12.04f\n",tmp_QE_val);

			norm_QE += tmp_QE_val/(tmp_lam*tmp_lam);
			
			reflectance_integrated += reflect_reflectance[i]*tmp_QE_val/(tmp_lam*tmp_lam);
			if (output_all_refl_spec == true)
			{
				printf("%12.04f %12.04f\n",tmp_lam,300*300*tmp_QE_val/(tmp_lam*tmp_lam));
			}
		}
		if (output_all_refl_spec == false)
		{
			printf("%12.04f\n",reflectance_integrated/norm_QE);
		}
	}
}
