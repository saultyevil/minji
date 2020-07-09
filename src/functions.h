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
/* mcrt.c */
void transport_photons(void);
/* parse.c */
char *get_command_line_arguments(int argc, char **argv);
/* photon.c */
void move_photon(struct Photon *p, double ds);
void create_photon(struct Photon *p, int number);
void init_photons(void);
/* random.c */
void init_gsl_seed(void);
double gsl_rand_num(double min, double max);
void get_random_optical_depth(double *const tau);
void get_random_theta_phi_direction(double *const theta, double *const phi);
/* scatter.c */
void scatter_photon(struct Photon *p);
/* time.c */
void print_current_time(void);
void print_time_elapsed(struct timespec start_time, char *message);
struct timespec get_current_time(void);
/* trans_phot.c */
void move_photon_to_scatter(struct Photon p);
/* utility.c */
void clean_up(void);
void mabort(const int error_code, char *fmt, ...);
