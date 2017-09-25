pub mod ht {
    use std::iter::FromIterator;
    use std::f64::consts::PI;

    pub fn cas(angle: f64) -> f64{
         angle.cos() + angle.sin()
    }

    fn eval_angle(k: usize, j: usize, n: usize) -> f64 {
        2.0 * PI * (j * k) as f64 / n as f64
    }

    /**
     * Discrete Hartley Transform
     * Formula:
     *      h_k = sum from j = 0 to N - 1 (a_j * cas (2 * pi * k * j / N))
     * Complexity: O(n^2)
     */
    pub fn dht<I: FromIterator<f64>>(a: &Vec<f64>) -> I {
        let n = a.len();
        (0..n).map(|k|
                (0..n).map(|j| a[j] * cas(eval_angle(k, j, n))
                ).sum()
         ).collect()
    }

    /**
     * Inverse Discrete Hartley Transform
     * Formula:
     *      h_k = 1/N * sum from j = 0 to N - 1 (a_j * cas (2 * pi * k * j / N))
     * Complexity: O(n^2)
     */
    pub fn idht<I: FromIterator<f64>>(a: &Vec<f64>) -> I {
        let n = a.len();
        (0..n).map(|k|
                ((0..n).map(|j| a[j] * cas(eval_angle(k, j, n))
                ).sum::<f64>() / n as f64)
         ).collect()
    }

//    /**
//     * Fast Hartley Transform
//     */
//    pub fn fht<I: FromIterator<f64>>(a: &Vec<f64>) -> I {
//    }
}


#[cfg(test)]
mod test {

    use ht;

    #[test]
    fn test_cas() {
        let v1  = vec![0.0, 1.0, 2.0, 3.0, 4.0 ,5.0];
        let res = vec![1.0,1.3817732906760363,0.4931505902785393,-0.8488724885405782,-1.4104461161715403,-0.6752620891999122];

        let res_r: Vec<f64> = v1.iter().map(|x| ht::cas(*x)).collect();
        assert_eq!(res_r, res);
    }

    #[test]
    fn test_dht() {
        let v = vec![1.0, 2.0, 3.0, 4.0, 5.0];
        let res_exp = vec![15.0, -5.94095, -3.3123, -1.6877, 0.94095];
        let res_real : Vec<f64> = ht::dht(&v);

        let eps = 0.00001;
        for i in 0..v.len() {
            assert!((res_exp[i] - res_real[i]).abs() < eps);
        }
    }

    #[test]
    fn test_idht() {
        let v = vec![1.0, 2.0, 3.0, 4.0, 5.0];
        let v1: Vec<f64> = ht::dht(&v);
        let v2: Vec<f64> = ht::idht(&v1);

        let eps = 0.00001;
        for i in 0..v.len() {
            assert!(v2[i] - v[i] < eps);
        }
    }

   // #[test]
   // fn test_fht() {
   //     let v = vec![1.0, 2.0, 3.0, 4.0, 5.0];
   //     let r1 = dht(&v);
   //     let r2 = fht(&v);
   //     assert_eq!(r1, r2);
   // }
}
