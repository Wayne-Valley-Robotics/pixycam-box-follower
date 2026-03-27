Proof of concept box seeker using the v1 pixycam

## References:

[pixycam documentation](https://docs.pixycam.com/wiki/doku.php?id=wiki:v1:arduino_api)

### TODO:

#### driving
- assemble robot
- wire motors and driver to arduino
- create drive() logic
- adjust pin values
- test basic movement


#### sensing
- teach pixycam signature with pixymon
- wire pixycam to arduino
- test sensing
- create following logic
- create idle/waiting logic (what to do when no object is detected? make sure detections that are absurdly small or otherwise unreasonable are filtered out)