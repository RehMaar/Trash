fn cas(angle: f64) -> f64{
     angle.cos() + angle.sin()
}

fn angle(k: usize, j: usize, n: usize) -> f64 {
    2.0 * PI * (j * k) as f64 / n as f64
}

pub fn dht(a: &mut Vec<f64>) {
    let n = a.len();
    *a = (0..n).map(|k|
           (0..n).map(|j| a[j] * cas(angle(k, j, n))
           ).sum()
    ).collect::<Vec<f64>>();
}

fn split_vec(a: &Vec<i32>) -> (Vec<i32>, Vec<i32>) {
    let mut x1 = Vec::new();
    let mut x2 = Vec::new();

    for i in 0..a.len()/2 {
        x1.push(a[2*i]);
        x2.push(a[2*i + 1]);
    }

    (x1, x2)
}


fn merge_vec(a: &mut Vec<i32>, x1: &Vec<i32>, x2: &Vec<i32>) {
    for i in 0..a.len() / 2 {
        a[2*i]     = x1[i];
        a[2*i + 1] = x2[i];
    }
}

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

pub fn fht(a: &mut Vec<f64>) {
    if a.len() <= MINIMUM_FHT_SUBSEQ {
        dht(a);
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
