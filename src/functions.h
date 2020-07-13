/* algebra.c */
int solve_quadratic(double a, double b, double c, double *solution);
int linear_interpolation(enum InterpolationMode mode, const double value, const double *array, const int npoints, int *index, double *fraction);
/* cartesian.c */
double cartesian_ds_to_cell_edge(const struct Photon p);
/* geometry.c */
double ds_to_sphere(const double radius, const struct Photon p);
/* grid_set.c */
void init_grid(void);
/* init.c */
void init_minji(void);
/* input.c */
void query_for_parameter_file(char *filename);
void open_parameter_file(char *filename);
void close_parameter_file(void);
void read_double(char *parameter, double *value);
void read_integer(char *parameter, int *value);
void get_string(char *parameter, char *value);
/* log.c */
void init_logfile(void);
void close_logfile(void);
void mlog(char *fmt, ...);
/* main.c */
int main(int argc, char **argv);
/* output.c */
void write_grid_to_file(void);
/* parse.c */
char *get_command_line_arguments(int argc, char **argv);
/* photon.c */
int find_grid_cell(const double *xyz);
void move_photon(struct Photon *p, const double ds);
void create_photon(struct Photon *p, int number);
void init_photons(void);
/* random.c */
void init_gsl_seed(void);
double gsl_rand_num(double min, double max);
void get_random_optical_depth(double *const tau);
void get_random_theta_phi_direction(double *theta, double *phi);
void random_spherical_vector(double *u, double radius);
/* scatter.c */
void scatter_photon(struct Photon *p);
/* spherical.c */
double spherical_ds_to_cell_edge(const struct Photon p);
int spherical_where_in_grid(const double *xyz);
/* time.c */
void print_current_time(void);
void print_time_elapsed(struct timespec start_time, char *message);
struct timespec get_current_time(void);
/* trans_phot.c */
void transport_photons(void);
/* utility.c */
void clean_up(void);
void exit_program(const int error_code, char *fmt, ...);
/* vector.c */
double dot_product(const double *u, const double *v);
double vector_magnitude(const double *u);
void subtract_vectors(const double *u, const double *v, double *w);
