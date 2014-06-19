Binary-Backoff
==============

The purpose of a backoff algorithm is to avoid collisions in networks when more than one station wishes to send a frame in a channel. In order to do this, collision detection must be handled during a timeslot, and if a collision is detected during this time slot, any sort of backoff algorithm is used to compute the next time slot colliding stations must wait for in order to retransmit. Colliding stations are usually assigned a random value from zero to the number returned by the backoff algorithm.
