import Data.Bool
import Control.Arrow ((***))

type State = (Bool, Bool)
type InputSignal = Bool
type OutputSignal = Bool
type GState = Int
type GSignalIn = Int
type GSignalOut = Int
type GEdge = (GSignalIn, (GState, GSignalOut))
type GGraph = [(GState, [GEdge])]

xor :: Bool -> Bool -> Bool
x `xor` y = (x || y) && not (x && y)

check' :: (InputSignal -> State -> (OutputSignal, State)) -> State -> [InputSignal] -> [(OutputSignal, State)]
check' _ _ [] = []
check' f s l = check'' s l
                where
                    check'' _ [] = []
                    check'' (q0, q1) (x0:list) = let (y0, (q0', q1')) = f x0 (q0, q1) in
                                                     (y0, (q0, q1)) : check'' (q0', q1') list

check :: (InputSignal -> State -> (OutputSignal, State)) -> State -> [GSignalIn] -> [(GSignalOut, GState)]
check f s = map (fromEnum *** getState) . check' f s . map toEnum

getState :: State -> GState
getState s = case s of
            (False, False) -> 2
            (False, True)  -> 3
            (True, False)  -> 1
            _              -> 4


checkG :: GGraph -> GState -> [GSignalIn] -> [(GSignalOut, GState)]
checkG _ _ [] = []
checkG g s (z:xs) = case lookup s g of
                        Nothing -> error "No such state."
                        Just l  -> case lookup z l of
                                        Nothing -> error "No such signal."
                                        Just (state, out)  -> (out, s) : checkG g state xs



list :: [Int]
list = [0,0,1,1,0,1,0,0,1,1,1] -- inputs

graph :: GGraph
graph =  [
          (1, [(0, (2, 0)), (1, (3, 0))]),
          (2, [(0, (2, 0)), (1, (1, 1))]),
          (3, [(0, (4, 1)), (1, (2, 0))]),
          (4, [(0, (2, 1)), (1, (3, 0))])
         ]


swp ((a,b), (d,c)) = ((a,d), (b,c))
cmpRes f = map swp $ zip (checkG graph 1 list) (check f (True, False) list)
cmpResTotal f = foldl (\b p -> b && cmpPair p) True $ zip (checkG graph 1 list) (check f (True, False) list)
            where cmpPair ((a,b), (d,c)) = a == d && b == c


eqOnDFF :: InputSignal -> State -> (OutputSignal, State)
eqOnDFF x0 (q0, q1) = (x0', (q0', q1'))
                where
                    phi = q1 && not x0
                    q0' = not q0 && (q1 `xor` x0)
                    x0' = q0' || (q0 && phi)
                    q1' = not q0 && phi || q0 && x0

eqOnRSFF :: InputSignal -> State -> (OutputSignal, State)
eqOnRSFF x0 (q0, q1) = (x0', (q0', q1'))
                    where
                        q0' = rs q0 r0 s0
                        q1' = rs q1 r1 s1
                        x0' = s0 || (not x0 && q0 && q1)
                        s1 = x0 && q0 && not q1
                        r0 = q0
                        r1 = q1 && (x0 `xor` q0)
                        s0 = not q0 && (x0 `xor` q1)
                        -- rs flip-flop table
                        rs q False False = q
                        rs _ False True  = True
                        rs _ True False  = False
                        rs _ _ _ = error "Forbidden state"

eqOnJKFF :: InputSignal -> State -> (OutputSignal, State)
eqOnJKFF x0 (q0, q1) = (x0', (q0', q1'))
                    where
                       q0' = jk q0 j0 k0
                       q1' = jk q1 j1 k1
                       j0 = not q0 && (x0 `xor` q1)
                       k0 = q0
                       j1 = x0 && q0 && not q1
                       k1 = q1 && (x0 `xor` q0)
                       x0' = j0 || (not x0 && q0 && q1)
                       jk q False False = q
                       jk _ False True  = False
                       jk _ True False  = True
                       jk q True True   = not q

eqOnTFF :: InputSignal -> State -> (OutputSignal, State)
eqOnTFF x0 (q0, q1) = (x0', (q0', q1'))
                where
                     x0' = not q0 && (q1 `xor` x0) || q0 && q1 && not x0
                     q1' = t q1 $ x0 && (q0 `xor` q1) || q0 && q1 && not x0
                     q0' = t q0 $ not q0 && (q1 `xor` x0) || q0
                     -- T prev_state new_state
                     t False q = q
                     t True  q = not q
