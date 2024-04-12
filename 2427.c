enum commit_action get_commit_action(struct rev_info *revs, struct commit *commit)
{
	if (commit->object.flags & SHOWN)
		return commit_ignore;
	if (revs->unpacked && has_sha1_pack(commit->object.sha1))
		return commit_ignore;
	if (revs->show_all)
		return commit_show;
	if (commit->object.flags & UNINTERESTING)
		return commit_ignore;
	if (revs->min_age != -1 && (commit->date > revs->min_age))
		return commit_ignore;
	if (revs->min_parents || (revs->max_parents >= 0)) {
		int n = commit_list_count(commit->parents);
		if ((n < revs->min_parents) ||
		    ((revs->max_parents >= 0) && (n > revs->max_parents)))
			return commit_ignore;
	}
	if (!commit_match(commit, revs))
		return commit_ignore;
	if (revs->prune && revs->dense) {
		/* Commit without changes? */
		if (commit->object.flags & TREESAME) {
			int n;
			struct commit_list *p;
			/* drop merges unless we want parenthood */
			if (!want_ancestry(revs))
				return commit_ignore;
			/*
			 * If we want ancestry, then need to keep any merges
			 * between relevant commits to tie together topology.
			 * For consistency with TREESAME and simplification
			 * use "relevant" here rather than just INTERESTING,
			 * to treat bottom commit(s) as part of the topology.
			 */
			for (n = 0, p = commit->parents; p; p = p->next)
				if (relevant_commit(p->item))
					if (++n >= 2)
						return commit_show;
			return commit_ignore;
		}
	}
	return commit_show;
}
