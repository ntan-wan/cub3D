/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:25:01 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/04/11 12:34:06 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINE_H
# define CUB3D_DEFINE_H

/* ********** OUTCOME ********** */

# define SUCCESS 0
# define ERROR 1

/* ********** SCREEN_DIMENSION *********** */

# define W_WIDTH 640
# define W_HEIGHT 640

/* ********** SIZE ********** */
# define CELL_SIZE 64
# define STEP_SIZE 4
# define ROTATE_SIZE 0.04

/* ********** MATH ********** */

# define PI 3.14159265

/* ********** KEYCODE ********** */

# ifdef __APPLE__
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_W 13
#  define KEY_S 1
#  define ESC 53
#  define SPACE_BAR 49
# else
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_W 119
#  define KEY_S 115
#  define ESC 65307
#  define SPACE_BAR 32
# endif

#endif