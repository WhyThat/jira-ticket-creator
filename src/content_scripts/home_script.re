open Relude.Option.Infix;

let prefixes = [|"AR", "ADS", "ASG", "SFV"|];

let getTicket = str => {
  Relude.Array.map(
    prefix => {
      let regex = Js.Re.fromString("(" ++ prefix ++ "-\\d+)(.*)");
      let result = Js.Re.exec_(regex, str);
      switch (result) {
      | None => None
      | Some(result) =>
        let captures = Js.Re.captures(result);
        switch (
          captures[1]->Js.Nullable.toOption,
          captures[0]->Js.Nullable.toOption,
        ) {
        | (Some(id), Some(full)) => Some((id, full))
        | _ => None
        };
      };
    },
    prefixes,
  )
  |> Relude.Array.find(Relude.Option.isSome)
  |> Relude.Option.flatten;
};

let baseUrl = "https://jira.strg.arte/browse/";
let buildUrl = ticketId => {
  baseUrl ++ ticketId;
};

let buildLink = ((ticketId, text)) => {
  let url = buildUrl(ticketId);
  {j| <a href=$url target="blank_">$text</a> |j};
};

let pr_title_element =
  Webapi.Dom.document |> Webapi.Dom.Document.querySelector(".js-issue-title");

let addLink = (el, link) =>
  switch (el) {
  | Some(el) => Webapi.Dom.Element.setInnerHTML(el, link)
  | None => ()
  };

pr_title_element
<#> Webapi.Dom.Element.textContent
>>= getTicket
<#> buildLink
<#> addLink(pr_title_element);
