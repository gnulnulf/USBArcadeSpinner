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
asmount();
knob();
//translate([ 0,50,0]) as();
//%as();
%encoder();
%plank();
translate([80,0,0]) busje();
translate([80,20,0]) busje();

module busje() {
    difference() {
        cylinder(d=8,h=7,$fn=60);
        translate([0,0,-1]) cylinder(d=7,h=10,$fn=60);
        
    }
}
module knob() {
    translate([0,0,-22]){ 
        difference() {
    cylinder(d=60,h=20,$fn=90);
            for (i =[1:2:360]) rotate([0,0,i])  translate([0,0,-1]) translate([30,-.5,-1]) rotate([0,0,45]) cube([1,1,30]);
            translate([0,0,5]) cylinder(d=8,h=20,$hn=30);
            translate([15,0,7]) cylinder(d=16,h=20,$hn=30);
            translate([-7,-7,7]) cube([25,14,7]);
            
        } //diff
    }
} //knob
module as() {
    cylinder(h=22,d=8,$fn=30);
    cylinder(h=2,d=14);
    translate([0,0,-10]) difference() {
        cylinder(h=50,d=6,$fn=30);
        translate([-5,-11.5,-1]) cube([10,10,60]);
}
    } 

module gear_big() {
translate([0,0,23]) rotate([0,0,0]) {
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
// m8
cylinder(h=50,d=8,$fn=30);
translate([0,0,21]) nut_mask(size=13);
    }
    
}

} //gear_big

module asmount() {
difference() {
    union() {
    translate([0,0,-1])  cylinder(h=22,d=28,$fn=60);
    translate([0,0,-1])  cylinder(h=1,d=34,$fn=60);
       }
    translate([0,0,-2])  cylinder(h=50,d=10,$fn=30);
    translate([0,0,-2])  cylinder(h=7+7+2,d=22.3,$fn=30);
    translate([0,0,16])  cylinder(h=7+2+2,d=22.3,$fn=30);
    
        
} //diff
} //asmount

module nut_mask(size=5.5) {
    translate([0,0,-28]) 
    cylinder(r=size / 2 / cos(180 / 6) + 0.05+0.1,h=size*0.75, $fn=6);
}

module gear_small() {
 translate([50,0,23])rotate([00,0,0])  
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