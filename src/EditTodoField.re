open Utils;

type state = string;

let component = ReasonReact.reducerComponent("EditTodoField");

let make = (~initialText, ~onSubmit, _) => {
  ...component,
  initialState: () => initialText,
  reducer: (newText, _text) => ReasonReact.Update(newText),
  render: ({state: text, reduce}) =>
    <input
      value=text
      _type="text"
      placeholder="Todo description"
      onChange=(reduce((evt) => valueFromEvent(evt)))
      onKeyDown=(
        (evt) =>
          if (ReactEventRe.Keyboard.key(evt) == "Enter") {
            onSubmit(text);
            (reduce(() => ""))()
          } else if (ReactEventRe.Keyboard.key(evt) == "Escape") {
            onSubmit(initialText);
            (reduce(() => ""))()
          }
      )
    />
};