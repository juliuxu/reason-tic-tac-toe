type state = {gameState: GameState.state};
let reducer = (state, action) => {
  gameState: GameState.reducer(state.gameState, action),
};
let make = () => {gameState: GameState.make()};