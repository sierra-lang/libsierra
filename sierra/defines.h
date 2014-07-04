/*
 * Copyright (c) 2013-2014, Saarland University
 */

#ifndef SIERRA_DEFINES_H
#define SIERRA_DEFINES_H

#define spmd(n) __attribute__((sierra_spmd(n)))
#define uniform __attribute__((sierra_vector(1)))
#define varying(n) __attribute__((sierra_vector(n)))
#define program_index(n) seq<n>()
#define spmd_mode(L) if ((bool varying(L)) true)

#endif
