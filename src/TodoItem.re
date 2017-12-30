open Utils;

open Types;

let component = ReasonReact.statelessComponent("TodoItem");

module Styles = {
  /* add root styles here */
  let root = ReactDOMRe.Style.make();
  let completed = ReactDOMRe.Style.make(~opacity="0.666", ~textDecoration="line-through", ());
};

let make = (~item: item, ~onToggle, ~onEditStart, ~onEditDone, _) => {
  ...component,
  render: (_) => {
    let style = Styles.root;
    let style = item.completed ? ReactDOMRe.Style.combine(style, Styles.completed) : style;
    <div style>
      <input
        _type="checkbox"
        onChange=((_) => onToggle())
        checked=(Js.Boolean.to_js_boolean(item.completed))
      />
      (
        item.editing ?
          <EditTodoField initialText=item.title onSubmit=((text) => onEditDone(text)) /> :
          <label onClick=((_) => onEditStart())> (str(item.title)) </label>
      )
    </div>
  }
};