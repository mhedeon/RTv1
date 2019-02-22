/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:08:48 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/22 19:38:44 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <float.h>

# define SCREEN_WIDTH 600
# define SCREEN_HEIGHT 600

# define THREADS 8
# define DEPTH 3
# define EPSILON ((double)0.000000001)

/*
**	from radians to degrees
*/
# define RAD(a) ((double)a * M_PI / 180.0)

/*
**	types of light
*/
# define AMBIENT 1
# define POINT 2

/*
**	types of objects
*/
# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4

/*
**	cast
*/
# define PLANE_D ((t_plane*)(plane->data))
# define SPHERE_D ((t_sphere*)(sphere->data))
# define CYLINDER_D ((t_cylinder*)(cylinder->data))
# define CONE_D ((t_cone*)(cone->data))

# define KEY e.type == SDL_KEYDOWN && e.key.keysym.sym

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef struct	s_light
{
	int			type;
	double		intens;
	t_vec		pos;
	struct s_light		*next;
}				t_light;

typedef struct	s_plane
{
	double		radius;
}				t_plane;

typedef struct	s_sphere
{
	double		radius_square;
}				t_sphere;

typedef struct	s_cylinder
{
	double		radius;
	double		height;
}				t_cylinder;

typedef struct	s_cone
{
	double		angle;
	double		height1;
	double		height2;
}				t_cone;

typedef struct	s_object
{
	int			type;
	t_vec	center;
	t_vec	normal;
	SDL_Color	color;
	int		specular;
	double		reflective;
	void		*data;
	void		(*intersect)();
	t_vec		(*get_normal)();
	struct s_object *next;
}				t_object;

typedef struct	s_fov
{
	t_vec		cam;
	t_vec		dir;
}				t_fov;


typedef struct	s_rtv
{
	SDL_Window	*win;
	SDL_Renderer	*ren;
	SDL_Texture	*tex;
	Uint32	*buff;
	SDL_Color	color;

	t_vec	camera;
	t_vec	dir;
	t_fov	fov;

	
	t_object *close_o;

	t_object *obj;
	t_light *light;

	int angle_y;
	double close;
	int angle_x;

	int start;
	int end;

	int depth;
}				t_rtv;

/*
**	main.c
*/
double lighting(t_rtv *rtv, t_fov pv, t_vec normal, int specular);
SDL_Color trace(t_rtv *rtv, t_fov fov);
void opti_plane(t_object *sphere, t_vec dir);
void opti_sphere(t_object *sphere, t_vec dir);
void opti_cylinder(t_object *cylinder, t_vec dir);
void opti_cone(t_object *cone, t_vec dir);
void opti(t_object *obj, t_vec dir);
void go(t_rtv *rtv);
void threads(t_rtv *rtv);
int rnd();

/*
**	intersect.c
*/
void			close_inters(t_rtv *rtv, t_fov fov, double min, double max);
void intersect_sphere(t_vec camera, t_vec dir, t_object *sphere, double *ts);
void intersect_plane(t_vec camera, t_vec dir, t_object *plane, double *ts);
void intersect_cylinder(t_vec camera, t_vec dir, t_object *cylinder, double *ts);
void intersect_cone(t_vec camera, t_vec dir, t_object *cone, double *ts);
double			limit_cylinder(t_object *cylinder, t_vec cam, double tmp, double t);
double			limit_cone(t_object *cone, t_vec cam, double tmp, double t);

/*
**	window,c
*/
void init(t_rtv *test);
void garbage(t_rtv *test);
void put_pixel(t_rtv *rtv, int x, int y);
void	set_pixel(t_rtv *test, SDL_Color *color, int x, int y);
void	clear_buffer(t_rtv *test);
void	screen_upd(t_rtv *test);

/*
**	vector.c
*/
double dot(t_vec v1, t_vec v2);
t_vec substruct(t_vec v1, t_vec v2);
double length(t_vec v1);
t_vec multiply(double k, t_vec v1);
t_vec add(t_vec v1, t_vec v2);
t_vec reflect(t_vec v1, t_vec v2);
/////////////////////////////////////////////////
t_vec rot_y(t_vec v, int angle);
t_vec rot_x(t_vec v, int angle);
t_vec rot_z(t_vec v, int angle);
t_vec direction(int x, int y, int angle_x, int angle_y);

/*
**	objects.c
*/
t_object *new_obj(t_object *obj, int type, t_vec center, t_vec normal, SDL_Color color, int specular, double reflect,  double radius,  double height,  double angle);
t_light *new_light(t_light *l, int type, double intens, t_vec pos);

/*
**	normal.c
*/
t_vec normalize(t_vec v);
t_vec normal_plane(t_rtv *rtv, t_vec camera, t_vec dir, t_vec point);
t_vec normal_sphere(t_rtv *rtv, t_vec camera, t_vec dir, t_vec point);
t_vec normal_cylinder(t_rtv *rtv, t_vec camera, t_vec dir, t_vec point);
t_vec normal_cone(t_rtv *rtv, t_vec camera, t_vec dir, t_vec point);

/*
**	scene.c
*/
void	get_data(t_rtv *rtv, char *name);

#endif