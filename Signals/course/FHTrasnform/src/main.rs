mod ht;
mod ht_fixed;
mod round;

extern crate rand;
use rand::Rng;

use round::{round, RoundingType};

use std::io::prelude::*;
use std::fs::File;

fn generate_vector(n: usize) -> Vec<f64> {
    let mut v = Vec::with_capacity(n);
    let mut rnd = rand::thread_rng();
    for _ in 0..n {
        v.push(rnd.gen_range::<f64>(0.0, 1024.0));
    }
    v
}

fn pow(i: f64) -> f64 {
    i * i
}
fn stdev(std: &Vec<f64>, cmp: &Vec<i32>) -> f64 {
    let div: f64 = (0..std.len()).map(|x| pow(std[x] - cmp[x] as f64)).sum();
        (div / std.len() as f64).sqrt()
}

fn len_stdev(v: &mut Vec<f64>, vsize: usize, rsize: usize, wsize: usize,
             rtype: RoundingType) -> f64 {

    let mut vf = round(&v.iter().map(|&x| x as i32).collect::<Vec<i32>>(),
                       vsize, rtype);
    ht::fht(v);
    ht_fixed::fht(&mut vf, rsize, wsize, rtype);

    stdev(&v, &vf)
}

fn main() {

    /* 1. Length - stdev correlation. */
    {
        let mut f = File::create("stdev.dat").unwrap();
        for i in 1..10 {
            let mut v = generate_vector(2 << i);
            let mut v1 = v.clone();
            let mut v2 = v.clone();
            let r  = len_stdev(&mut v,  8, 16, 8, RoundingType::Round);
            let r1 = len_stdev(&mut v1, 8, 16, 8, RoundingType::Cut);
            let r2 = len_stdev(&mut v2, 8, 16, 8, RoundingType::CutInc);
            if let Err(_) = write!(f, "{} {} {} {}\n", 2 << i, r, r1, r2) {
                println!("Error while writing data to file");
                return
            }
        }
    }
    /* 2. 2/4-bit input. */
    {
        let mut f = File::create("stdev_i.dat").unwrap();
        for i in 1..10 {
            let mut v = generate_vector(2 << i);
            let mut v1 = v.clone();

            let r  = len_stdev(&mut v,  2, 16, 8, RoundingType::Round);
            let r1 = len_stdev(&mut v1, 4, 16, 8, RoundingType::Round);
            if let Err(_) = write!(f, "{} {} {}\n", 2 << i, r, r1) {
                println!("Error while writing data to file");
                return
            }
        }
    }
    /* 3. 2/4-bit weight. */
    {
        let mut f = File::create("stdev_w.dat").unwrap();
        for i in 1..10 {
            let mut v = generate_vector(2 << i);
            let mut v1 = v.clone();

            let r  = len_stdev(&mut v,  8, 16, 2, RoundingType::Round);
            let r1 = len_stdev(&mut v1, 8, 16, 4, RoundingType::Round);
            if let Err(_) = write!(f, "{} {} {}\n", 2 << i, r, r1) {
                println!("Error while writing data to file");
                return
            }
        }
    }
}
