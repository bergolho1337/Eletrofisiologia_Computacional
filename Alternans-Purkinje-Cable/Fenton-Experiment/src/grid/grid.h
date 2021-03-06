//
// Created by sachetto on 29/09/17.
//

#ifndef FENTON_GRID_H
#define FENTON_GRID_H

//#include "../cell/cell.h"
#include "../purkinje/purkinje.h"
#include "../monodomain/config/config_parser.h"

#include <string>

#include <cassert>
#include <cstdlib>
#include <cstdio>

struct grid 
{
    // The purkinje network
    Graph *the_purkinje_network;
    
    // Size of the space discretization
    double dx;
};


struct grid* new_grid();
void configure_grid_from_options (struct grid *the_grid, struct user_options *options);
void clean_and_free_grid(struct grid* the_grid);
void clean_grid(struct grid *the_grid);

/*
void initialize_grid(struct grid *the_grid, double side_length);
void construct_grid(struct grid *the_grid);
void initialize_and_construct_grid(struct grid *the_grid, double side_length);
void print_grid(struct grid* the_grid, FILE *output_file);
void print_grid_with_scar_info(struct grid *the_grid, FILE *output_file, bool binary);

bool print_grid_and_check_for_activity(const struct grid *the_grid, FILE *output_file, const int count, const bool binary);

void order_grid_cells (struct grid *the_grid);

void set_grid_flux(struct grid *the_grid);

bool refine_grid_with_bound(struct grid* the_grid, double refinement_bound, double min_h);
void refine_grid(struct grid* the_grid, int num_steps);
void refine_grid_cell_at(struct grid *the_grid, uint32_t cell_number);
void refine_fibrotic_cells(struct grid *the_grid);
void refine_border_zone_cells(struct grid *the_grid);

bool derefine_grid_with_bound(struct grid *the_grid, double derefinement_bound, double max_h);
void derefine_all_grid (struct grid* the_grid);
void derefine_grid_inactive_cells (struct grid* the_grid);

void print_grid_matrix(struct grid *the_grid, FILE* output_file);
void print_grid_vector(struct grid* the_grid, FILE *output_file, char name);
double * grid_vector_to_array(struct grid *the_grid, char name, uint32_t *num_lines);

void save_grid_domain (struct grid * the_grid, const char *file_name);

void lock_grid(struct grid *the_grid);

void unlock_grid(struct grid *the_grid);


void initialize_and_construct_grid_purkinje (struct grid *the_grid);
void initialize_grid_purkinje (struct grid *the_grid);
void construct_grid_purkinje (struct grid *the_grid);
*/
#endif //MONOALG3D_GRID_H
