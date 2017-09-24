pub mod ht {
    use std::iter::FromIterator;
    use std::f64::consts::PI;

    pub fn cas(angle: f64) -> f64{
         angle.cos() + angle.sin()
    }

    pub fn eval_angle(k: usize, j: usize, n: usize) -> f64 {
        2.0 * PI * (j * k) as f64 / n as f64
    }

    /**
     * h_k = sum from j = 0 to N - 1 (a_j * cas (2 * pi * k * j / N))
     */
    pub fn dht<I: FromIterator<f64>>(a: &Vec<f64>) -> I {
        let n = a.len();
        (0..n).map(|k|
                (0..n).map(|j| a[j] * cas(eval_angle(k, j, n))
                ).sum()
         ).collect()
    }

//  fn fht() { }

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
    fn test_eval_angle() {

    }

    #[test]
    fn test_dht() {
        let scale = 1000.0;
        let v = vec![1.0, 2.0, 3.0, 4.0, 5.0];
        let res_exp = vec![15.0, -5.94095, -3.3123, -1.6877, 0.94095];
        let res_real : Vec<f64> = ht::dht(&v);

        let res_exp_scaled: Vec<i64>  = res_exp.iter().map(|x| (x * scale) as i64).collect();
        let res_real_scaled: Vec<i64> = res_real.iter().map(|x| (x * scale) as i64).collect();

        assert_eq!(res_exp_scaled, res_real_scaled);

    }

//  #[test]
//  fn test_fht() {
//  }
}
