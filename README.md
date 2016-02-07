# SwarmCoordinator

Uses relative power levels of beacons for MLAT (multilateration - 2D) to coordinate swarms of robots relative to a beacon coordinator (robot with multiple beacons). Percent error is calculated and utilized to adjust the final assumed location of a robot - more erroneous values affect weighting less, leaving a barycenter as the final relative position.

The multilateration is solved through finding the radical center of each possible pair of beacons, then calculating the barycenter of the system after error weighting. If the power levels assume that the radii do not intercept, the error is calculated accordingly - the same applies to when the overlap of the power levels is excessive.
