#ifndef _VALIDATE_INPUT_H_
#define _VALIDATE_INPUT_H_

static int handle_invalid_mode();

static int handle_invalid_arguments_count();

static int validate_generate_arguments(int argc, char **argv);

static int validate_analyze_arguments(int argc, char **argv);

static int validate_generate_mode(int argc, char **argv);

static int validate_generate_consistent_mode(int argc, char **argv);

static int validate_analyze_mode(int argc, char **argv);

static int validate_mode(char *mode, int argc, char **argv);

int validate_input(int argc, char **argv);

#endif
