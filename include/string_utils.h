#ifndef STRING_UTILS_H 
#define STRING_UTILS_H

int
u_strcomp (char * c1 , char * c2);

int 
u_strlen (char * s);

void 
u_add_t_end (char * s1 , char * s2);

void 
u_strcpy (char * src , char * dest);

void 
u_clear_buffer (char * buffer , int buff_size);

void 
u_trim (char * buffer , int buff_size);

#endif /* STRING_UTILS_H */
