#include <unistd.h>
#include <fcntl.h>

	int     v[9];/*v[3]='.'v[4]='o'v[5]='x'v[6]=ibv[2]=bv[0]=hv[1]=w*/
/*v[7]=yv[8]=z*/
void    ft_get_map(int y, char *argv);
void    find_x(int x, int y, char r, char m[v[0]][v[1]]);
int     block_x(int p, char m[v[0]][v[1]]);
void    place_x(char m[v[0]][v[1]]);
void    ft_init(char *av);

void    place_x(char m[v[0]][v[1]]) {
    int     n[3];

    n[0] = 0;
    while (++v[2] != -1 && n[0] == 0) {
        n[2] = -1;
        v[6] = 0;
        while (++n[2] < v[0] && v[6] == 0 && n[2] < v[3] - v[2] + 1) {
            n[1] = -1;
            while (++n[1] < v[1] && v[6] == 0 && n[1] < v[1] - v[2] + 1)
                if (m[n[2]][n[1]] == v[3])
                    find_x(n[1], n[2], v[3], m);
 	}
        if (v[6] == 2) v[2]++;
            else n[0] = block_x(v[2] - 1, m);
    }
    n[2] = -1;
    while (++n[2] < v[0]) {
        n[1] = -1;
        while (++n[1] < v[1]) write(1, &m[n[2]][n[1]], 1);
        write(1, "\n", 1);
    }
}
int    block_x(int p, char m[v[0]][v[1]]) {
    int     n[3];

    n[0] = 0;
    while (n[0] == 0) {
        v[2] = p;
        v[6] = 0;
        n[1] = -1;
        while (++n[1] < v[0] && n[0] == 0 && n[1] < v[3] - v[2] + 1) {
            n[2] = -1;
            while (++n[2] < v[1] && n[0] == 0 && n[2] < v[1] - v[2] + 1) {
                if (m[n[1]][n[2]] == v[3])
                    find_x(n[2], n[1], v[3], m);
                if (v[6] == 2) {
                    find_x(n[2], n[1], v[5], m);
                    n[0]++;
                }
            }
        }
        if (n[0] == 0) p--;
    }
    return 1;
}
void    find_x(int x, int y, char r, char m[v[0]][v[1]]) {
    int     n[4];

    n[0] = y - 1;
    n[1] = 0;
    n[2] = 0;
    while (++n[0] < y + v[2] && n[0] < v[0] && n[1] == 0) {
        n[3] = x - 1;
        while (++n[3] < x + v[2] && n[3] < v[1] && n[1] == 0)
            if (m[n[0]][n[3]] == v[3] && n[1] == 0) {
                m[n[0]][n[3]] = r;
                n[2]++;
            }
            else
                n[1]++;
    }
    if (n[1] == 0 && n[2] == v[2] * v[2]) v[6] = 2;/* if found a match */
}
void    ft_get_map(int y, char *av) {
    char    m[v[0]][v[1]];
    int     n[6];

    n[0] = 6;
    while (--n[0] > -1) if (n[0] != 0) n[n[0]] = 0;
    while (av[++n[0]] && n[3] == 0) {
        if (av[n[0]] == '\n') {
            n[4]++;
	    if (n[4] == 2) n[5] = n[1] - 1;
	    if (n[5] != n[1] - 1 && n[4] >= 2) n[3] = 1;
	    n[1] = 0;
            y++;
        }
	else
	    if (n[4] > 1 && av[n[0]] != v[3] && av[n[0]] != v[4] &&
	     av[n[0]] != v[5])
		n[3] = 1;
    	if (y >= 0 && av[n[0]] != '\n')
            m[y][++n[1] - 1] = av[n[0]];
    }
    if (n[3] == 1)
	 write(1, "map error\n", 10);
    else 
	place_x(m);
}
void	ft_init(char *av) {
    int     n[4];

    n[0] = 3;
    n[1] = 0;
    n[2] = 0;
    while (--n[0] > -1) v[n[0]] = 0;
    while (av[++n[0]] != '\0' && n[1] != 2) {
        if (av[n[0]] >= '0' && av[n[0]] <= '9')
            v[0] = v[0] * 10 + av[n[0]] - 48;
        else 
            n[2]++;
        if (n[2] == 1) v[3] = av[n[0]];
        if (n[2] == 2) v[4] = av[n[0]];
        if (n[2] == 3) v[5] = av[n[0]];
        if (av[n[0]] == '\n') n[1]++;
        if(n[1] == 1) v[1]++;
    }/* gets w and h */
    v[1]--;
    ft_get_map(-1, av);/* and then solves */
}
void    main(int argc, char **argv) {
	char	n;

	v[7] = 0;
	while (++v[7] < argc) {
		int	*f;
		char	av[999999];

		v[8] = -1;
		*f = open(argv[v[7]], O_RDONLY, 1);
		while (read(*f, &n, 1)) av[++v[8]] = n;
		av[++v[8]] = '\0';
		ft_init(av);
		close(*f);
	}
	if (argc == 1) 
		write(1, "map error\n", 10);
}
