fn signum(a: i32) -> i32 {
    if a > 0 {
        1
    } else if a < 0 {
        -1
    } else {
        0
    }
}

#[derive(Copy, Clone)]
pub enum RoundingType {
    Cut,
    CutInc,
    Round,
}

/**
 * The rounding algorithm, accepts a number, how many bits should be left
 * unaffected, and how to round the number.
 */
pub fn round(a: &Vec<i32>, size: usize, rtype: RoundingType) -> Vec<i32> {
    let s = if a.iter().any(|&x| x < 0) { size - 1 } else { size };

    if let Some(Some(n)) = a.iter().map(
        |&x| (0..31).rev().find(|i| x.abs() & (1 << i) != 0))
        .filter(|x| x.is_some()).max()
    {
        if n >= s {
            a.iter().map(|&x| {
                let t = x.abs();
                let mo = n + 1 - s;
                signum(x) * {
                    match rtype {
                        RoundingType::Cut =>
                            t & (!(1i32 << s) << mo),
                        RoundingType::CutInc =>
                            (1 + (t >> mo)) << mo,
                        RoundingType::Round =>
                            if t & (1 << (n - s)) != 0 {
                                (1 + (t >> mo)) << mo
                            } else {
                                t & (!(1i32 << s) << mo)
                            },
                    }
                }
            }).collect()
        } else {
            a.clone()
        }
    } else {
        a.clone()
    }
}

#[cfg(test)]
mod tests {
    #[test]
    fn test_round() {
        use super::round;
        use super::RoundingType;

        assert_eq!(round(&vec![14], 8, RoundingType::Cut),    vec![14]);
        assert_eq!(round(&vec![14], 2, RoundingType::Cut),    vec![12]);
        assert_eq!(round(&vec![14], 1, RoundingType::Cut),    vec![8 ]);
        assert_eq!(round(&vec![14], 8, RoundingType::CutInc), vec![14]);
        assert_eq!(round(&vec![14], 2, RoundingType::CutInc), vec![16]);
        assert_eq!(round(&vec![14], 1, RoundingType::CutInc), vec![16]);
        assert_eq!(round(&vec![14], 8, RoundingType::Round),  vec![14]);
        assert_eq!(round(&vec![14], 2, RoundingType::Round),  vec![16]);
        assert_eq!(round(&vec![14], 1, RoundingType::Round),  vec![16]);
        assert_eq!(round(&vec![31], 8, RoundingType::Round),  vec![31]);
        assert_eq!(round(&vec![32], 1, RoundingType::Round),  vec![32]);

        assert_eq!(round(&vec![-1, -1, 4, -1, -1], 2, RoundingType::Round),
            vec![0, 0, 4, 0, 0]);
    }
}

