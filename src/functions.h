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
 * mcrt.c
 */

int mcrt_iterations (void);

/*
 * photon.c
 */

int define_photon (Photon *photon, int photon_number);
int init_photons (void);
int traverse_phot_ds (Photon *p, double ds);

/*
 * planar_geo.c
 */

int allocate_planar_grid (void);
int get_planar_params (void);
int init_planar_geo (void);

/*
 * random.c
 */

double gsl_rand_num (double min, double max);
int init_gsl_seed (void);
double random_tau (void);
int random_theta_phi (double *theta, double *phi);

/*
 * read_pars.c
 */

int get_double (char *par_name, double *value);
int get_int (char *par_name, int *value);
int get_string (char *par_name, char *value);
int get_optional_int (char *par_name, int *value);
int get_optional_double (char *par_name, double *value);
int input_double (char *par_name, double *value);
int input_int (char *par_name, int *value);
int input_string (char *par_name, char *value);
int find_par_file (char *file_path);
int init_parameter_file (char *par_filepath);

/*
 * scatter.c
 */

int scatter_phot (Photon *photon);

/*
 * setup.c
 */

int init_geo (void);

/*
 * spherical_geo.c
 */

int init_spherical_geo (void);

/*
 * time.c
 */

int print_time (void);
struct timespec get_time (void);
int print_duration (struct timespec start_time, char *message);

/*
 * trans_phot.c
 */

int dist_to_cell_wall (Photon *p, double *d_cell);
int dist_to_edge (Photon *p, double *s_max);
int trans_phot (Photon *p);

/*
 * utility.c
 */

void Exit (int error_code, char *fmt, ...);
int Log (char *fmt, ...);
int Log_parallel (char *fmt, ...);
int Log_verbose (char *fmt, ...);
int Log_error (char *fmt, ...);
double min_double (int n, ...);
