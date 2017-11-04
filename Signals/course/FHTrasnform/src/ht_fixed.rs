use round::{round, RoundingType};

use std::f32::consts::PI;

const MINIMUM_FHT_SUBSEQ: usize = 4;

fn cas(angle: f32) -> f32{
     angle.cos() + angle.sin()
}

/** (2 pi j k) / n */
fn angle(k: usize, j: usize, n: usize) -> f32 {
    2.0 * PI * (j * k) as f32 / n as f32
}

/**
 * Discrete Hartley Transform
 * Formula:
 *      h_k = sum from j = 0 to N - 1 (a_j * cas (2 * pi * k * j / N))
 * Complexity: O(n^2)
 */
pub fn dht(a: &mut Vec<i32>, rsize: usize, wsize: usize, rtype: RoundingType) {
    let n = a.len();
    *a = (0..n).map(|k|
          round(&vec![(0..n).map(|j| {
                    let w = round(&vec![(cas(angle(k, j, n)) * 10.0) as i32], wsize, rtype)[0];
                    round(&vec![a[j] * w / 10], rsize, rtype)[0]
                }).sum()], rsize, rtype)[0]
    ).collect::<Vec<i32>>();
}

/**
 * Split vector to two smaller ones by index parity.
 */
fn split_vec(a: &Vec<i32>) -> (Vec<i32>, Vec<i32>) {
    let mut x1 = Vec::new();
    let mut x2 = Vec::new();

    for i in 0..a.len()/2 {
        x1.push(a[2*i]);
        x2.push(a[2*i + 1]);
    }

    (x1, x2)
}

/**
 * Merge two splited vectors.
 */
fn merge_vec(a: &mut Vec<i32>, x1: &Vec<i32>, x2: &Vec<i32>) {
    for i in 0..a.len() / 2 {
        a[2*i]     = x1[i];
        a[2*i + 1] = x2[i];
    }
}

/**
 * Evaluate FHT forumla for k'th iteration.
 */
fn hartley(a: &mut Vec<i32>, k: usize, asize: usize, wsize: usize, rtype: RoundingType) -> i32 {
    let n = a.len();
    let h = a.len() / 2 ;

    let (signed, ang, idx_x1, idx_x2, idx_x2_n) = if k < h {
        let n = if k == 0 { 1 } else { 2*(h - k) + 1};
        (1, k, 2 * k, 2*k + 1, n)
    } else {
        let n = if k == h { 1 } else { 2*(n - k) + 1};
        (-1, k - h, 2 * (k - h), 2*(k - h) + 1, n )
    };

    let angle_cos = round(&vec![((angle(ang, 1, n)).cos() * 10.0) as i32], wsize, rtype)[0];
    let angle_sin = round(&vec![((angle(ang, 1, n)).sin() * 10.0) as i32], wsize, rtype)[0];

    let v = a[idx_x1] + signed * a[idx_x2]   * angle_cos / 10
                      + signed * a[idx_x2_n] * angle_sin / 10;

    round(&vec![v], asize, rtype)[0]
}

/**
 * Fast Hartley Transform
 *
 * if seq.len() < PREDEFINED_CONSTANT
 *   1. Evaluate dht().
 * else
 *   1. Split seq into two subseq: odd and even.
 *   2. Evaluate fht for this subseq.
 *   3. Evaluate other staff.
 */
pub fn fht(a: &mut Vec<i32>, rsize: usize, wsize: usize, rtype: RoundingType) {
    if a.len() <= MINIMUM_FHT_SUBSEQ {
        dht(a, rsize, wsize, rtype);
        return;
    }

    let (mut x1, mut x2) = split_vec(a);

    fht(&mut x1, rsize, wsize, rtype);
    fht(&mut x2, rsize, wsize, rtype);

    merge_vec(a, &x1, &x2);
    let mut b = Vec::with_capacity(a.len());
    for i in 0..a.len() {
        b.push(hartley(a, i, rsize, wsize, rtype));
    }
    *a = b;
}
