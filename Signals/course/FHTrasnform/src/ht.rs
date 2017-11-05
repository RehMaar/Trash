use std::f64::consts::PI;

    
const MINIMUM_FHT_SUBSEQ: usize = 4;

fn cas(angle: f64) -> f64{
     angle.cos() + angle.sin()
}

/** (2 pi j k) / n */
fn angle(k: usize, j: usize, n: usize) -> f64 {
    2.0 * PI * (j * k) as f64 / n as f64
}

/**
 * Discrete Hartley Transform
 * Formula:
 *      h_k = sum from j = 0 to N - 1 (a_j * cas (2 * pi * k * j / N))
 * Complexity: O(n^2)
 */
pub fn dht(a: &mut Vec<f64>) {
    let n = a.len();
    *a = (0..n).map(|k|
           (0..n).map(|j| a[j] * cas(angle(k, j, n))
           ).sum()
    ).collect::<Vec<f64>>();
}

/**
 * Split vector to two smaller ones by index parity.
 */
fn split_vec(a: &Vec<f64>) -> (Vec<f64>, Vec<f64>) {
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
fn merge_vec(a: &mut Vec<f64>, x1: &Vec<f64>, x2: &Vec<f64>) {
    for i in 0..a.len() / 2 {
        a[2*i] = x1[i];
        a[2*i + 1] = x2[i];
    }
}

/**
 * Evaluate FHT forumla for k'th iteration.
 */
fn hartley(a: &mut Vec<f64>, k: usize) -> f64 {
    let n = a.len();
    let h = a.len() / 2 ;

    let (signed, ang, idx_x1, idx_x2, idx_x2_n) = if k < h {
        let n = if k == 0 { 1 } else { 2*(h - k) + 1};
        (1.0, k, 2 * k, 2*k + 1, n)
    } else {
        let n = if k == h { 1 } else { 2*(n - k) + 1};
        (-1.0, k - h, 2 * (k - h), 2*(k - h) + 1, n )
    };

    a[idx_x1] + signed * a[idx_x2]   * (angle(ang, 1, n)).cos()
                     + signed * a[idx_x2_n] * (angle(ang, 1, n)).sin()

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
pub fn fht(a: &mut Vec<f64>) {
    if a.len() <= MINIMUM_FHT_SUBSEQ {
        dht(a);
       // println!("DHT: {:?}", a);
        return;
    }

    let (mut x1, mut x2) = split_vec(a);

    fht(&mut x1);
    fht(&mut x2);

    merge_vec(a, &x1, &x2);
    let mut b = Vec::with_capacity(a.len());
    for i in 0..a.len() {
        b.push(hartley(a, i));
    }
    *a = b;
}

#[cfg(test)]
mod test_ht {

    use ht;
    extern crate rand;
    use rand::Rng;
    
    fn generate_vector(n: usize) -> Vec<f64> {
        let mut v = Vec::with_capacity(n);
        let mut rnd = rand::thread_rng();
        for _ in 0..n {
            v.push(rnd.gen::<f64>());
        }
        v
    }

    #[test]
    fn test_dht() {
        let mut v = vec![1.0, 2.0, 3.0, 4.0, 5.0];
        let res_exp = vec![15.0, -5.94095, -3.3123, -1.6877, 0.94095];
        ht::dht(&mut v);

        let eps = 0.001;
        for i in 0..v.len() {
            assert!(v[i] - res_exp[i] < eps);
        }
    }

    #[test]
    fn test_fht_8() {
        let mut v = generate_vector(8);
        let mut v1=  v.clone();

        ht::dht(&mut v);
        ht::fht(&mut v1);

        let eps = 0.00001;
        for i in 0..v.len() {
            assert!(v1[i] - v[i] < eps);
        }
    }

    #[test]
    fn test_fht_16() {
        let mut v = generate_vector(16);
        let mut v1=  v.clone();

        ht::dht(&mut v);
        ht::fht(&mut v1);

        let eps = 0.00001;
        for i in 0..v.len() {
            assert!(v1[i] - v[i] < eps);
        }
    }

    #[test]
    fn test_fht_1024() {
        let mut v = generate_vector(1024);
        let mut v1=  v.clone();

        ht::dht(&mut v);
        ht::fht(&mut v1);

        let eps = 0.00001;
        for i in 0..v.len() {
            assert!(v1[i] - v[i] < eps);
        }
    }
}
