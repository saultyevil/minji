/* ***************************************************************************
 *
 * @file
 *
 * @author
 *
 * @brief
 *
 * @details
 *
 * ************************************************************************** */

/*
 * default_pars.c
 */

int init_default_pars (void);

/*
 * grid_set.c
 */

void init_grid (void);

/*
 * mcrt.c
 */

int mcrt_iterations (void);

/*
 * output.c
 */

void write_grid_to_file (char *filename);

/*
 * photon.c
 */

void define_photon (Photon * p, int photon_number);
void init_photons (void);
void traverse_phot_ds (Photon * p, double ds);

/*
 * random.c
 */

double gsl_rand_num (double min, double max);
void init_gsl_seed (void);
double random_tau (void);
void random_theta_phi (double *theta, double *phi);

/*
 * read_pars.c
 */

void get_double (char *par_name, double *value);
void get_int (char *par_name, int *value);
void get_string (char *par_name, char *value);
void get_optional_int (char *par_name, int *value);
void get_optional_double (char *par_name, double *value);
void find_par_file (char *file_path);
void init_parameter_file (char *par_filepath);

/*
 * scatter.c
 */

void scatter_phot (Photon * p);

/*
 * setup.c
 */

void init_geo (void);


/*
 * time.c
 */

struct timespec get_time (void);
void print_time (void);
void print_duration (struct timespec start_time, char *message);

/*
 * trans_phot.c
 */

void ds_to_cell_wall (Photon *p, double *ds);
void dist_to_edge (Photon * p, double *s_max);
void trans_phot (Photon * p);

/*
 * utility.c
 */

void Exit (int error_code, char *fmt, ...);
void Log (char *fmt, ...);
void Log_parallel (char *fmt, ...);
void Log_verbose (char *fmt, ...);
void Log_error (char *fmt, ...);