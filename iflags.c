#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <string.h>


#define SHOW_FLAG(f) { str_prepare(#f); printf("  %s%c\n", str, (f & ifa->ifa_flags) ? 'x' : ' '); }

const char guide[] = "............... ";  /* at least as long as the longest flag name */
char str[sizeof(guide)];
void str_prepare(char *n)
{
  size_t i;
  strcpy(str, guide);
  for (i = 0; i < strlen(n); i++)
    str[i] = n[i];
}

int main()
{
  int res;
  struct ifaddrs *ifaddrs, *ifa;

  res = getifaddrs(&ifaddrs);
  if (res != 0)
  {
    perror("getifaddrs");
    return 1;
  }

  for (ifa = ifaddrs; ifa != NULL; ifa = ifa->ifa_next)
  {
    if (ifa->ifa_addr->sa_family != AF_PACKET)
      continue;

    printf("%d: %s\n", if_nametoindex(ifa->ifa_name), ifa->ifa_name);
    SHOW_FLAG(IFF_UP);
    SHOW_FLAG(IFF_BROADCAST);
    SHOW_FLAG(IFF_DEBUG);
    SHOW_FLAG(IFF_LOOPBACK);
    SHOW_FLAG(IFF_POINTOPOINT);
    SHOW_FLAG(IFF_RUNNING);
    SHOW_FLAG(IFF_NOARP);
    SHOW_FLAG(IFF_PROMISC);
    SHOW_FLAG(IFF_NOTRAILERS);
    SHOW_FLAG(IFF_ALLMULTI);
    SHOW_FLAG(IFF_MASTER);
    SHOW_FLAG(IFF_SLAVE);
    SHOW_FLAG(IFF_MULTICAST);
    SHOW_FLAG(IFF_PORTSEL);
    SHOW_FLAG(IFF_AUTOMEDIA);
    SHOW_FLAG(IFF_DYNAMIC);

    /* 
     * ifr_flags, the struct returned from the SIOCGIFFLAGS ioctl, has the flag
     * in ifr_flags, which is a short. For this reason, these flags are not
     * exposed to userspace via libc, but only via netlink. Send in a patch? :)
     *
     * SHOW_FLAG(IFF_LOWER_UP);
     * SHOW_FLAG(IFF_DORMANT);
     * SHOW_FLAG(IFF_ECHO);
     */

  }

  freeifaddrs(ifa);

  return 0;
}

