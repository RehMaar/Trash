mod ht;
mod ht_fixed;
mod round;

use round::{round, RoundingType};
extern crate rand;
use rand::Rng;

fn generate_vector(n: usize) -> Vec<f64> {
    let mut v = Vec::with_capacity(n);
    let mut rnd = rand::thread_rng();
    for _ in 0..n {
        v.push(rnd.gen_range::<f64>(0.0, 1024.0));
    }
    v
}

fn main() {
    let mut v  = generate_vector(8); //vec![255.0, 136.0, 2.0, 69.0, 8.0, 89.0, 107.0, 1.0];
    let vf = v.iter().map(|&x| x as i32).collect::<Vec<i32>>(); //vec![255, 136, 2, 69, 8, 89, 107, 1];

    println!("Float point");
    println!("{:?}", v);
    let mut v1 = v.clone();
    ht::dht(&mut v);
    println!("DHT: {:?}", v);
    ht::fht(&mut v1);
    println!("FHT: {:?}", v1);

    println!("Fixed point");

    let asize = 8;
    let rsize = 16;
    let wsize = 8;
    println!("Cut");
    let rtype = RoundingType::Cut;
    let mut vf_r = round(&vf, asize, rtype);
    println!("{:?}", vf_r);
    let mut vf1 = vf_r.clone();
    ht_fixed::dht(&mut vf_r, rsize, wsize, rtype);
    println!("DHT: {:?}", vf_r);
    ht_fixed::fht(&mut vf1, rsize, wsize, rtype);
    println!("FHT: {:?}", vf1);

    println!("IncCut");
    let rtype = RoundingType::CutInc;
    let mut vf_r = round(&vf, asize, rtype);
    println!("{:?}", vf_r);
    let mut vf1 = vf_r.clone();
    ht_fixed::dht(&mut vf_r, rsize, wsize, rtype);
    println!("DHT: {:?}", vf_r);
    ht_fixed::fht(&mut vf1, rsize, wsize, rtype);
    println!("FHT: {:?}", vf1);

    println!("Cut");
    let rtype = RoundingType::Round;
    let mut vf_r = round(&vf, asize, rtype);
    println!("{:?}", vf_r);
    let mut vf1 = vf_r.clone();
    ht_fixed::dht(&mut vf_r, rsize, wsize, rtype);
    println!("DHT: {:?}", vf_r);
    ht_fixed::fht(&mut vf1, rsize, wsize, rtype);
    println!("FHT: {:?}", vf1);
}
