open Utils;

open Types;

let component = ReasonReact.statelessComponent("TodoItem");

let getClassName = ({completed}) => "item" ++ (completed ? " completed" : "");

let make = (~item, ~onToggle, ~onEditStart, ~onEditDone, _) => {
  ...component,
  render: (_) =>
    <div className=(getClassName(item))>
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
};