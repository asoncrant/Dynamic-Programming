import sys
import copy

##############################################################
## Skeleton code of dynamic programming version of changeMoney
## Arguments:
## - total  : (integer) total amount of money to make
## - unit   : list of containing units of bills in integer
## - stored : dictionary containing a stored information to avoid
##            redundancy   
##############################################################
def dpChangeMoney(total, units, stored):
    key = ":".join(map(str, [total] + units))
    if (key not in stored.keys()):
        n = len(units)
        if ( total == 0 ): ## exact
            return [{}]
        elif ( total < 0 ):
            return []
        else:
            ret = []
            n = len(units)
            for i in range(0,n):
                sols = copy.deepcopy(dpChangeMoney(total-units[i], units[i:n], stored))
                for sol in sols:
                    if ( units[i] in sol ):
                        sol[units[i]] += 1
                    else:
                        sol[units[i]] = 1
                    ret.append(sol)
            stored[key] = ret 
    return stored[key]


##############################################################
## TODO: implement the function above.
##############################################################

dollars = int(sys.argv[1])
bills   = [int(x) for x in sys.argv[2:len(sys.argv)]]
ways = dpChangeMoney(dollars, bills, {})
print("There are " + str(len(ways)) + " possible ways to make "+str(dollars))
for way in ways:
    print(sorted(way.items()))
