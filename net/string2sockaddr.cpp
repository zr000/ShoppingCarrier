from https://github.com/cloudwu/netout/blob/master/netout.c

union sockaddr_all {
	struct sockaddr s;
	struct sockaddr_in v4;
	struct sockaddr_in6 v6;
};

static int
string_to_sockaddr(lua_State *L, int addr_idx, int port_idx, union sockaddr_all *sa, socklen_t *retsz) {
	size_t sz;
	const char * buf = luaL_checklstring(L, addr_idx, &sz);
	int port = luaL_checkinteger(L, port_idx);
	int family;
	void *ptr;
	if (memchr(buf, ':', sz)) {
		// ipv6
		family = AF_INET6;
		*retsz = sizeof(sa->v6);
		ptr = &sa->v6.sin6_addr;
		sa->v6.sin6_port = htons(port);
	} else {
		// ipv4
		family = AF_INET;
		*retsz = sizeof(sa->v4);
		ptr = &sa->v4.sin_addr;
		sa->v4.sin_port = htons(port);
	}
	if (inet_pton(family, buf, ptr) != 1) {
		return -1;
	}
	sa->s.sa_family = family;

	return family;
}