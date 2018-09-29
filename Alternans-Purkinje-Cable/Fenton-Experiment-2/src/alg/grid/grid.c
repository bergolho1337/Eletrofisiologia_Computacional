//
// Created by sachetto on 29/09/17.
//

#include "grid.h"
#include <assert.h>
#include "inttypes.h"

struct grid* new_grid() 
{
    struct grid* result = (struct grid*) malloc(sizeof(struct grid));
    result->first_cell = NULL;
    result->active_cells = NULL;

    // Purkinje
    result->the_purkinje_network = new_graph();

    return result;
}



void print_grid (struct grid *the_grid, FILE *output_file) {

    struct cell_node *grid_cell = the_grid->first_cell;

    double center_x, center_y, center_z, half_face;
    double v;

    while (grid_cell != 0) {

        if (grid_cell->active) {

            center_x = grid_cell->center_x;
            center_y = grid_cell->center_y;
            center_z = grid_cell->center_z;

            v = grid_cell->v;
            half_face = grid_cell->half_face_length;

            fprintf (output_file, "%lf,%lf,%lf,%lf,%lf\n", center_x, center_y, center_z, half_face, v);
        }
        grid_cell = grid_cell->next;
    }
}

void order_grid_cells (struct grid *the_grid) {

    struct cell_node *grid_cell;
    grid_cell = the_grid->first_cell;

    //Here we allocate the maximum number of cells we will need for the whole simulation
    if (the_grid->active_cells == NULL) 
    {
        the_grid->active_cells = (struct cell_node **)malloc (sizeof (struct cell_node *) * the_grid->number_of_cells);
    }

    uint32_t counter = 0;
    while (grid_cell != 0) 
    {
        if (grid_cell->active) 
        {
            grid_cell->grid_position = counter;
            the_grid->active_cells[counter] = grid_cell;
            counter++;
        }

        grid_cell = grid_cell->next;
    }

    the_grid->num_active_cells = counter;
}

void clean_grid (struct grid *the_grid) 
{

    assert(the_grid);
    uint32_t number_of_cells = the_grid->number_of_cells;

    struct cell_node *grid_cell = the_grid->first_cell;

    // We will only delete the cells nodes in Purkinje case
    if(grid_cell) 
    {

        // Deleting cells nodes.
        while (grid_cell) 
        {

            struct cell_node *next = grid_cell->next;
            free_cell_node(grid_cell);
            grid_cell = next;

        }
    }

    if (the_grid->the_purkinje_network) 
    {
        free_graph(the_grid->the_purkinje_network);
    }

}

void clean_and_free_grid(struct grid* the_grid) {

    assert(the_grid);

    clean_grid(the_grid);

    if (the_grid->active_cells) {
        free (the_grid->active_cells);
    }

    free (the_grid);
}

// Prints grid discretization matrix.
void print_grid_matrix (struct grid *the_grid, FILE *output_file) {

    assert(the_grid);
    assert(output_file);

    struct cell_node *grid_cell;
    grid_cell = the_grid->first_cell;
    struct element element;
    struct element *cell_elements;

    while (grid_cell != 0) {
        if (grid_cell->active) {

            cell_elements = grid_cell->elements;
            size_t max_el = sb_count(cell_elements);

            for(size_t i = 0; i < max_el; i++) {

                element = cell_elements[i];
                if(element.cell != NULL) {
                    fprintf(output_file, "%" PRIu32 " " "%" PRIu32 " %.15lf\n",
                            grid_cell->grid_position + 1,
                            (element.column) + 1,
                            element.value);
                }
                else {
                    break;
                }

            }

        }
        grid_cell = grid_cell->next;
    }
}


void print_grid_vector(struct grid* the_grid, FILE *output_file, char name)
{
    struct cell_node *grid_cell;
    grid_cell = the_grid->first_cell;

    while( grid_cell != 0 )
    {
        if( grid_cell->active )
        {
            if(name == 'b')
                fprintf(output_file, "%.15lf\n", grid_cell->b);
            else if (name == 'x')
                fprintf(output_file, "%.15lf\n", grid_cell->v);
        }
        grid_cell = grid_cell->next;

    }

}

double * grid_vector_to_array(struct grid *the_grid, char name, uint32_t *num_lines) {
    struct cell_node *grid_cell;
    grid_cell = the_grid->first_cell;

    *num_lines = the_grid->num_active_cells;
    double *vector = (double*) malloc(*num_lines*sizeof(double));

    while( grid_cell != 0 )
    {
        if( grid_cell->active )
        {
            if(name == 'b')
                vector[grid_cell->grid_position] = grid_cell->b;
            else if (name == 'x')
                vector[grid_cell->grid_position] = grid_cell->v;
        }
        grid_cell = grid_cell->next;

    }

    return vector;

}

void save_grid_domain (struct grid * the_grid, const char *file_name) {
    struct cell_node *grid_cell = the_grid->first_cell;
    FILE *f = fopen (file_name, "w");

    while (grid_cell != 0) {
        if (grid_cell->active) {
            fprintf (f, "%lf,%lf,%lf,%lf\n", grid_cell->center_x, grid_cell->center_y,
                     grid_cell->center_z, grid_cell->half_face_length);
        }
        grid_cell = grid_cell->next;
    }
    fclose (f);
}

void initialize_grid_purkinje (struct grid *the_grid)
{
    assert(the_grid);

    the_grid->number_of_cells = 0;
}

void construct_grid_purkinje (struct grid *the_grid)
{
    assert(the_grid);

    double side_length = the_grid->the_purkinje_network->dx;
    double half_side_length = side_length / 2.0f;
    double quarter_side_length = side_length / 4.0f;
    printf("Side length = %lf\n",side_length);
    printf("Half_side length = %lf\n",half_side_length);
    printf("Quarter_side length = %lf\n",quarter_side_length);

    int total_nodes = the_grid->the_purkinje_network->total_nodes;
    
    // Create an array of cell nodes
    struct cell_node **cells = (struct cell_node**)malloc(sizeof(struct cell_node*)*total_nodes);
    for (int i = 0; i < total_nodes; i++)
        cells[i] = new_cell_node();
    
    // Pass through the Purkinje graph and set the cell nodes.
    struct node *n = the_grid->the_purkinje_network->list_nodes;
    for (int i = 0; i < total_nodes; i++)
    {
        
        if (i == 0)
            set_cell_node_data (cells[i],side_length,half_side_length,0,\
                        NULL,NULL,NULL,NULL,NULL,NULL,\
                        NULL,cells[i+1],i,0,\
                        n->x,n->y,n->z);
        else if (i == total_nodes-1)
            set_cell_node_data (cells[i],side_length,half_side_length,0,\
                        NULL,NULL,NULL,NULL,NULL,NULL,\
                        cells[i-1],NULL,i,0,\
                        n->x,n->y,n->z);
        else
            set_cell_node_data (cells[i],side_length,half_side_length,0,\
                        NULL,NULL,NULL,NULL,NULL,NULL,\
                        cells[i-1],cells[i+1],i,0,\
                        n->x,n->y,n->z);

        // Do not refine the Purkinje cells !
        cells[i]->can_change = false;

        n = n->next;
    }
    
    // Grid initialization
    the_grid->first_cell = cells[0];
    the_grid->number_of_cells = total_nodes;
    
}

void initialize_and_construct_grid_purkinje (struct grid *the_grid)
{
    assert(the_grid);

    initialize_grid_purkinje(the_grid);
    construct_grid_purkinje(the_grid);
}