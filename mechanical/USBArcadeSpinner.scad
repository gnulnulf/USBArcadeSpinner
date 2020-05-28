//!
//! @file 
//! @brief USB arcade spinner
//!     Play 
 
//! @version 1.0
//! @author Arco van Geest <arco@appeltaart.mine.nu>
//! @copyright 2020 Arco van Geest <arco@appeltaart.mine.nu> All right reserved.
//! @license  Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)  https://creativecommons.org/licenses/by-sa/4.0/

//! @date 20200528 Initial version

//! @todo 


// You can get this file from http://www.thingiverse.com/thing:3575
use <parametric_involute_gear_v5.0.scad>

//gear_base();
gear_big();
gear_small();
mount();
translate([ 0,50,0]) as();
%encoder();
%plank();

module as() {
    cylinder(h=20,d=8,$fn=30);
    cylinder(h=2,d=14);
    translate([0,0,-10]) difference() {
        cylinder(h=50,d=6,$fn=30);
        translate([-5,-11.5,-1]) cube([10,10,60]);
}
    } 

module gear_big() {
translate([0,0,21]) rotate([0,0,0]) {
    difference() {
    gear (circular_pitch=100*2,	gear_thickness = 8,rim_thickness = 8,
	hub_thickness = 8,
    bore_diameter=1,
    number_of_teeth=152/2
	);
            translate([0,0,-10]) difference() {
        cylinder(h=50,d=6,$fn=30);
        translate([-5,-11.5,-1]) cube([10,10,60]);
}
    }
    
}

} //gear_big

module gear_small() {
 translate([50,0,21])rotate([00,0,0])  
    difference() {
        gear (circular_pitch=100*2,
	gear_thickness = 8,
    rim_thickness = 8,
	hub_thickness = 8,
    bore_diameter=1,
    number_of_teeth=26/2
	);
            translate([0,0,-10]) difference() {
        cylinder(h=50,d=6,$fn=30);
        translate([-5,-11.5,-1]) cube([10,10,60]);
}
        
    }//diff

} //gear small


module encoder() {
 translate([50,0,19])rotate([00,0,0]) { 
      translate([0,0,0]) difference() {
        cylinder(h=28,d=6,$fn=30);
        translate([-5,-11.5,-1]) cube([10,10,60]);
      }
      translate([0,0,12]) cylinder(d=7,h=7,$fn=30);
      translate([0,0,19]) cylinder(d=18,h=8);
      
  }
} //encoder

module mount() {
 translate ([50-10,0-20,19])rotate([00,0,0]) {
    difference() {
       union() {
          translate([0,0,16]) cube([20,40,3]);
          translate([0,0,0]) cube([20,3,16]);
          translate([0,37,0]) cube([20,3,16]);
          translate([0,-10,-1]) cube([20,13,3]);
          translate([0,37,-1]) cube([20,13,3]);
       }    
      translate([10,20,-1]) cylinder(d=7,h=30,$fn=30);
      translate([10,-5,-2]) cylinder(d=5,h=30,$fn=30);
      translate([10,45,-2]) cylinder(d=5,h=30,$fn=30);
   }
  }
} //mount


module plank() {
    difference() {
    translate([-75,-75,0]) cube([150,150,18]);
        translate([0,0,-1]) cylinder(d=28,h=20,$fn=30);
    }
}