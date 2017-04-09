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

swp ((a,b), (d,c)) = ((a,d),(b,c))
cmpRes f = map swp $ zip (checkG graph 1 list) (check f (True, False) list)

eqOnDFF :: InputSignal -> State -> (OutputSignal, State)
eqOnDFF x0 (q0, q1) = (x0', (q0', q1'))
                where
                    phi = q1 && not x0
                    q0' = not q0 && (q1 `xor` x0)
                    x0' = q0' || (q0 && phi)
                    q1' = not q0 && phi || q0 && x0

eqOnTFF :: InputSignal -> State -> (OutputSignal, State)
eqOnTFF x0 (q0, q1) = (x0', (q0', q1'))
                where
                    phi = q1 && not x0
                    q0' = not q0 && (q1 `xor` x0)
                    x0' = q0' || (q0 && phi)
                    q1' = not q0 && phi || q0 && x0

