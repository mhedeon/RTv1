/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:55:32 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/27 19:42:20 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object		*add_plane(t_object *obj)
{
	t_object	*start;
	t_object	*new;

	start = obj;
	while (obj != NULL && obj->next != NULL)
		obj = obj->next;
	new = (t_object *)malloc(sizeof(t_object));
	new->type = PLANE;
	new->center = (t_vec) { 0.0, 0.0, 0.0 };
	new->normal = (t_vec) { 0.0, 1.0, 0.0 };
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = 5.0;
	new->reflective = 0.0;
	new->data = (t_plane *)malloc(sizeof(t_plane));
	((t_plane*)(new->data))->radius = INFINITY;
	new->intersect = intersect_plane;
	new->get_normal = normal_plane;
	new->next = NULL;
	if (obj == NULL)
		obj = new;
	else
		obj->next = new;
	return (start == NULL ? obj : start);
}

t_object		*add_sphere(t_object *obj)
{
	t_object	*start;
	t_object	*new;

	start = obj;
	while (obj != NULL && obj->next != NULL)
		obj = obj->next;
	new = (t_object *)malloc(sizeof(t_object));
	new->type = SPHERE;
	new->center = (t_vec) { 0.0, 0.0, 0.0 };
	new->normal = (t_vec) { 0.0, 1.0, 0.0 };
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = 5.0;
	new->reflective = 0.0;
	new->data = (t_sphere *)malloc(sizeof(t_sphere));
	((t_sphere*)(new->data))->radius_square = 1.0;
	new->intersect = intersect_sphere;
	new->get_normal = normal_sphere;
	new->next = NULL;
	if (obj == NULL)
		obj = new;
	else
		obj->next = new;
	return (start == NULL ? obj : start);
}

t_object		*add_cylinder(t_object *obj)
{
	t_object	*start;
	t_object	*new;

	start = obj;
	while (obj != NULL && obj->next != NULL)
		obj = obj->next;
	new = (t_object *)malloc(sizeof(t_object));
	new->type = CYLINDER;
	new->center = (t_vec) { 0.0, 0.0, 0.0 };
	new->normal = (t_vec) { 0.0, 1.0, 0.0 };
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = 5.0;
	new->reflective = 0.0;
	new->data = (t_cylinder *)malloc(sizeof(t_cylinder));
	((t_cylinder*)(new->data))->height = INFINITY;
	((t_cylinder*)(new->data))->radius = 1.0;
	new->intersect = intersect_cylinder;
	new->get_normal = normal_cylinder;
	new->next = NULL;
	if (obj == NULL)
		obj = new;
	else
		obj->next = new;
	return (start == NULL ? obj : start);
}

t_object		*add_cone(t_object *obj)
{
	t_object	*start;
	t_object	*new;

	start = obj;
	while (obj != NULL && obj->next != NULL)
		obj = obj->next;
	new = (t_object *)malloc(sizeof(t_object));
	new->type = CONE;
	new->center = (t_vec) { 0.0, 0.0, 0.0 };
	new->normal = (t_vec) { 0.0, -1.0, 0.0 };
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = 5.0;
	new->reflective = 0.0;
	new->data = (t_cone *)malloc(sizeof(t_cone));
	((t_cone*)(new->data))->angle = tan(RAD(15));
	((t_cone*)(new->data))->height1 = INFINITY;
	((t_cone*)(new->data))->height2 = INFINITY;
	new->intersect = intersect_cone;
	new->get_normal = normal_cone;
	new->next = NULL;
	if (obj == NULL)
		obj = new;
	else
		obj->next = new;
	return (start == NULL ? obj : start);
}

void			start_object(t_rtv *rtv, int *fd)
{
	char		*line;
	t_object	*tmp;

	tmp = rtv->obj;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (get_next_line(*fd, &line))
	{
		if (!check_option_o(tmp, line))
			if (!ft_strcmp(line, "#"))
			{
				free(line);
				return ;
			}
		free(line);
	}
}
